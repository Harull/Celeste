#include "MovingTile.h"
#include "Game.h"
#include "MovementComponent.h"
#include "TimerManager.h"
#include "GravityComponent.h"

MovingTile::MovingTile(const EntityType _type, const Vector2f& _position, const Vector2f& _size, const string& _path, Grid* _owner):Tile(_type, _position, _size, _path, _owner)
{
	destination.push_back(_position);
	components.push_back(new MovementComponent(this,false,true));
	currentDestination = Vector2f();
	collisionReaction = [this](int _collisionSide, int _collisionSideBinary) {Move(_collisionSide, _collisionSideBinary); };
	indexDestination = 0;
	activated = false;
	
	yeetMultiplier = 3;
	currentYeetTimerIndex = 0;
	timeSinceDestination = sf::Clock();
	isYeeted = false;
	previousNonNullDirection = sf::Vector2f();
	dirWithVelocity = sf::Vector2f();
	yeetFinalMove = sf::Vector2f();
}

void MovingTile::CarryCharacter()
{
	Character* _character = Game::GetInstance().GetPlayer()->GetCharacter();
	MovementComponent* _thisMvCp = GetComponent<MovementComponent>();

	if (!_character || !(_character->GetShape()->getGlobalBounds().intersects(shape->getGlobalBounds()))|| !_thisMvCp->GetCanMove())
		return;

	if (CollisionComponent* _collision = _character->GetComponent<CollisionComponent>())
	{
		CollisionInfos _currentInfos = _collision->CheckCollision(true);
		if (_currentInfos.collisionSideBinary & COLLIDE_UP || 
			_currentInfos.collisionSideBinary & COLLIDE_RIGHT || 
			_currentInfos.collisionSideBinary & COLLIDE_LEFT )
		{
			if (MovementComponent* _chMvCp = Game::GetInstance().GetPlayer()->GetCharacter()->GetComponent<MovementComponent>())
			{
				sf::Vector2f _dirWithVelocity = _thisMvCp->GetDirection() * _thisMvCp->GetVelocity();
				_chMvCp->Move({ _dirWithVelocity.x / _chMvCp->GetVelocity(), _dirWithVelocity.y } );
			}
		}
	}

	
}

void MovingTile::YeetCharacter(const bool _fromPreviousLocation)
{
	Character* _character = Game::GetInstance().GetPlayer()->GetCharacter();
	if (!_character) return;

	_character->GetComponent<GravityComponent>()->ApplyGravity();
	currentYeetTimerIndex = 0;

	MovementComponent* _thisMvCp = GetComponent<MovementComponent>();

	if (_fromPreviousLocation)
	{
		dirWithVelocity = previousNonNullDirection * _thisMvCp->GetVelocity();
	}
	else
	{
		dirWithVelocity = _thisMvCp->GetDirection() * _thisMvCp->GetVelocity();
	}

	if (Timer* _currentYeetTimer = TimerManager::GetInstance().GetApproximately("YeetTimer"))
	{
		_currentYeetTimer->Reset();
	}
	else if (MovementComponent* _chMvCp = Game::GetInstance().GetPlayer()->GetCharacter()->GetComponent<MovementComponent>())
	{
		new Timer("YeetTimer", [&]() {

			MovementComponent* _mvComponent = Game::GetInstance().GetPlayer()->GetCharacter()->GetComponent<MovementComponent>();
			yeetFinalMove = (dirWithVelocity * yeetMultiplier) / static_cast<float>(((currentYeetTimerIndex / 10) + 1));

			if (std::abs(yeetFinalMove.x) < 2 && std::abs(yeetFinalMove.y) < 2)
			{
				isYeeted = false;
				return;
			}

			_mvComponent->Move(yeetFinalMove, false);
			currentYeetTimerIndex++;

			}, sf::seconds(0), true, true);
		
	}
	_character->GetComponent<GravityComponent>()->ApplyGravity(true);
}

bool MovingTile::TryYeetCharater()
{
	Character* _character = Game::GetInstance().GetPlayer()->GetCharacter();
	if (timeSinceDestination.getElapsedTime() < sf::seconds(0.5f) && _character->GetIsJumping())
	{
		isYeeted = true;
		YeetCharacter(true);
	}
	else if (_character->GetIsJumping())
	{
		isYeeted = true;
		YeetCharacter();
	}

	return false;
}

void MovingTile::Move(int _collisionSide, int _collisionSideBinary)
{
	if (_collisionSide != COLLIDE_UP)return;
	if (_collisionSideBinary != ENTITY_CHARACTER)return;
	MovementComponent* _move = GetComponent<MovementComponent>();
	
	if (activated)return;

	indexDestination = 1;
	activated = true;
	_move->SetCanMove(true);
	UpdateDirection();
}

void MovingTile::Update()
{
	MovementComponent* _move = GetComponent<MovementComponent>();
	if (GetShape()->getGlobalBounds().intersects(Game::GetInstance().GetPlayer()->GetCharacter()->GetShape()->getGlobalBounds()))
	{
		//std::cout << "Moving tile dir:" << _move->GetDirection().x << " | " << _move->GetDirection().y << std::endl;
		if (TryYeetCharater())return;
		CarryCharacter();
	}

	Entity::Update();

	if(!_move->IsAtLocation(currentDestination)|| !_move->GetCanMove())return;
	if (indexDestination == 0)
	{
		_move->SetCanMove(false);
		previousNonNullDirection = _move->GetDirection();
		_move->SetDirection({ 0,0 });
		new Timer("Reload" + id, [this]() {
			activated = false;
			}, seconds(2.5), true, false);
		
		return;
		
	}
	else if (indexDestination >= destination.size()-1)
	{
		UpdateDirection();
		timeSinceDestination.restart();
		indexDestination = 0;
	}
	else
	{
		indexDestination++;
	}
	
	_move->SetCanMove(false);
	previousNonNullDirection = _move->GetDirection();
	_move->SetDirection({ 0,0 });
	new Timer("Stop" + id, [this]() {
		MovementComponent* _move = GetComponent<MovementComponent>();
		UpdateDirection();
		_move->SetCanMove(true);
		}, seconds(2.5), true, false);
	
}

void MovingTile::Reset()
{
	currentDestination = destination[0];
	indexDestination = 0;
	shape->setPosition(currentDestination);
	activated = false;
	isYeeted = false;
	GetComponent<MovementComponent>()->SetCanMove(false);
	
}
