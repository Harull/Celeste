
#include "Character.h"
#include "TextureManager.h"
#include "MovementComponent.h"
#include "GravityComponent.h"
#include "AnimationComponent.h"
#include "CollisionComponent.h"
#include "TimerManager.h"
#include"Portal.h"
#include "Game.h"
#include"EntityManager.h"
#include "SoundManager.h"
#include"Camera.h"
#include"Grid.h"


	#define CHARACTER_TEXTURE "Character/Slave.png"
	#define DEAD_ZONE 50.f

	Character::Character(const sf::Vector2f _size, const sf::Vector2f _position, const int _maxYVelocity, const bool _isVisible)
		: Entity(EntityData("Character", ENTITY_CHARACTER, _position, _size),
			{ new MovementComponent(this, 2.5f, sf::Vector2f(0,0), true),
				new GravityComponent(this, 4.5f),
				new CollisionComponent(this) })
	{
		float _time = float(RandomMaxMin(60, 20));
		new Timer("PortalAppears", [this]() {
			const sf::Vector2f& _shapePos = shape->getPosition();
			Portal* _portal = new Portal({ _shapePos.x + 10, _shapePos.y + 4 } , shape->getGlobalBounds().getSize());
			GetComponent<MovementComponent>()->SetCanMove(false);

			new Timer("AnimationPortal", [this]() {
				SoundManager::GetInstance().Play("Luigi173.wav");
				GetComponent<AnimationComponent>()->Refresh();
				GetComponent<AnimationComponent>()->SetDirection(ANIM_DIR_IN_PORTAL); }, sf::seconds(1.f));
			data.inPortal = true;
			_portal->Teleport();

			}, seconds(_time));

		maxYVelocity = _maxYVelocity;
		wallJumpDirection = 0;
		currentJumpTimerIndex = 0;
		checkPoint = Vector2f(0.f, 0.f);

		isJumping = false;
		isClimbing = false;
		isDashing = false;

		dashCount = 1;
		maxDashCount = 1;
		currentDashVelocity = _maxYVelocity * 2;
		currentDashTimerIndex = 0;
		dashDirectionBuffer = Vector2i(0, 0);
		collisionSideBinBonkBuffer = 0;
		lastWallCollisionSide = COLLIDE_NONE;

		hasWon = false;

		InitShape();
		const Vector2f& _sizeA = Vector2f(24.4f, 41.f);
		const ReadDirection& _readDirection = READ_RIGHT;
		const bool _toRepeat = true;
		const int _count = 8;
		const int _countStop = 1;
		const float _speedA = 0.1f;
		AnimationDirection direction = ANIM_DIR_NONE;

		AnimationComponent* _animation = new AnimationComponent(this, CHARACTER_TEXTURE, {
			AnimationData("WalkRight", Vector2f(12.0f, 7.f), _sizeA, _readDirection, ANIM_DIR_RIGHT, _toRepeat, _count, _speedA),
			AnimationData("WalkLeft", Vector2f(11.f, 53.f), _sizeA, _readDirection, ANIM_DIR_LEFT, _toRepeat, _count, _speedA),
			AnimationData("JumpRight", Vector2f(12.f, 100.f), Vector2f(22.f,47.f), _readDirection, ANIM_DIR_JUMP_RIGHT, _toRepeat, _countStop, _speedA),
			AnimationData("FallRight", Vector2f(38.f, 102.f), Vector2f(23.f,44.f), _readDirection, ANIM_DIR_FALL_RIGHT, _toRepeat, _countStop, _speedA),
			AnimationData("JumpLeft", Vector2f(38.f, 151.f), Vector2f(23.f,47.f), _readDirection, ANIM_DIR_JUMP_LEFT, _toRepeat, _countStop, _speedA),
			AnimationData("FallLeft", Vector2f(13.f, 153), Vector2f(23.f,45.f), _readDirection, ANIM_DIR_FALL_LEFT, _toRepeat, _countStop, _speedA),

			AnimationData("GrabLeftWall", Vector2f(12.f, 396.f), Vector2f(21.f, 40.f), _readDirection, ANIM_DIR_GRAB_LEFT, _toRepeat, 1, _speedA * 2.f),
			AnimationData("GrabRightWall", Vector2f(12.f, 348.f), Vector2f(21.f, 40.f), _readDirection, ANIM_DIR_GRAB_RIGHT, _toRepeat, 1, _speedA * 2.f),
			AnimationData("ClimbLeftWall", Vector2f(12.f, 300.f), Vector2f(21.f, 40.f), _readDirection, ANIM_DIR_CLIMB_LEFT, _toRepeat, 4, _speedA * 2.f),
			AnimationData("ClimbRightWall", Vector2f(14.f, 252.f), Vector2f(21.f, 40.f), _readDirection, ANIM_DIR_CLIMB_RIGHT, _toRepeat, 4, _speedA * 2.f),

			AnimationData("DashRight", Vector2f(12.f, 450.f), Vector2f(25.f, 42.f), _readDirection, ANIM_DIR_DASH_RIGHT, _toRepeat, 8, _speedA),
			AnimationData("DashLeft", Vector2f(12.f, 500.f), Vector2f(25.f, 42.f), _readDirection, ANIM_DIR_DASH_LEFT, _toRepeat, 8, _speedA),


			AnimationData("EnterInPortal", Vector2f(10.f, 540.f), Vector2f(31.f, 40.f), _readDirection, ANIM_DIR_IN_PORTAL, false, 9, _speedA * 2.f,ANIM_DIR_INVICIBLE),
			AnimationData("OutofPortal", Vector2f(13.f, 589.f), Vector2f(27.f, 40.f), _readDirection, ANIM_DIR_OUT_PORTAL, false, 9,_speedA * 2.f),


			AnimationData("None", Vector2f(12.f, 203), _sizeA, _readDirection, ANIM_DIR_NONE, _toRepeat, 1, _speedA * 2.f),
			AnimationData("invisible",{0.f,0.f},{0.f,00.f},READ_RIGHT,ANIM_DIR_INVICIBLE,_toRepeat,1,0.1f),
			}, direction);


		/* _name,  _start, _size,
			ReadDirection& _readDirection, AnimationDirection& _direction,
			bool _canLoop, int _count, float _timeBetween)*/


		components.push_back(_animation);
		shape->setOutlineThickness(2);
		shape->setOutlineColor(sf::Color::Red);
		shape->setFillColor(sf::Color::Transparent);
		data = PortalData();
	}

	void Character::InitShape()
	{
		TextureManager::GetInstance().Load(shape, CHARACTER_TEXTURE);
	}

	void Character::StopAllJumps()
	{
		if (Timer* _currentJumpTimer = TimerManager::GetInstance().GetApproximately("JumpTimer"))
			_currentJumpTimer->Stop();
		if (Timer* _currentJumpTimer = TimerManager::GetInstance().GetApproximately("WJTimer"))
			_currentJumpTimer->Stop();
	}

	bool Character::MovingLeftRight(const sf::Event& _event)
	{
		sf::Keyboard::Key _leftKey = sf::Keyboard::Q;
		sf::Keyboard::Key _rightKey = sf::Keyboard::D;

		if (_event.type != sf::Event::JoystickMoved)
			if (_event.key.code != _leftKey && _event.key.code != _rightKey)return false;

		MovementComponent* _mvComponent = GetComponent<MovementComponent>();
		if (isClimbing)
		{
			_mvComponent->SetDirection({ 0,0 });
			return false;
		}

		sf::Vector2f _direction = _mvComponent->GetDirection();


		float _xDirection;
		if (_event.type == sf::Event::JoystickMoved)
		{
			float _axisXPosition = sf::Joystick::getAxisPosition(0, sf::Joystick::X);
			_xDirection = (_axisXPosition <= -DEAD_ZONE) ? -1.f : _axisXPosition >= DEAD_ZONE ? 1.f : 0.f;
		}
		else
			_xDirection = -(sf::Keyboard::isKeyPressed(_leftKey) * 1.f) + sf::Keyboard::isKeyPressed(_rightKey) * 1.f;

		sf::Vector2f _newDirection(_xDirection, _direction.y);
		_mvComponent->SetDirection(_newDirection);
		return true;
	}

	bool Character::Jump(const sf::Event& _event)
	{
		sf::Keyboard::Key _jumpKey = sf::Keyboard::Space;
		if (_event.type == sf::Event::JoystickButtonPressed && _event.joystickButton.button != 0)return false;
		if (_event.type == sf::Event::KeyPressed && _event.key.code != _jumpKey)return false;
		if (WallJump(_event)) return false;

		GravityComponent* _grav = GetComponent<GravityComponent>();
		_grav->Update();

		if (isJumping || (!(GetComponent<CollisionComponent>()->CheckCollision().collisionSideBinary & COLLIDE_UP))) return false;
		isJumping = true;
		currentJumpTimerIndex = 0;

		StopAllJumps();
		Timer* _jumpTimer = new Timer("JumpTimer", [&]() {
			MovementComponent* _mvComponent = GetComponent<MovementComponent>();

			sf::Vector2f _direction = _mvComponent->GetDirection();

			if (currentJumpTimerIndex == 0)
			{
				currentYVelocity = maxYVelocity;
			}
			else
				currentYVelocity = maxYVelocity / ((currentJumpTimerIndex / 12) + 1);

			if (currentYVelocity < 2) return;


			//std::cout << "Move Jump" << std::endl;
			_mvComponent->Move({ 0.f, -currentYVelocity * static_cast<float>(Game::GetInstance().GetSenseOfGravity()) });
			currentJumpTimerIndex++;
			}, sf::seconds(0), true, true);
		SoundManager::GetInstance().Play("jump.wav");

		return true;
	}

	bool Character::WallJump(const sf::Event& _event)
	{
		sf::Keyboard::Key _jumpKey = sf::Keyboard::Space;
		if (_event.type == sf::Event::JoystickButtonPressed && _event.joystickButton.button != 0)return false;
		if (_event.type == sf::Event::KeyPressed && _event.key.code != _jumpKey)return false;

		int _collisionSideBinary = GetComponent<CollisionComponent>()->CheckCollision(true).collisionSideBinary;

		if (_collisionSideBinary & COLLIDE_UP || (!(_collisionSideBinary & COLLIDE_RIGHT) && !(_collisionSideBinary & COLLIDE_LEFT))) return false;
		currentJumpTimerIndex = 0;
		isClimbing = false;

		wallJumpDirection = (_collisionSideBinary & COLLIDE_RIGHT) ? 1 : -1;

		StopAllJumps();
		Timer* _jumpTimer = new Timer("WJTimer", [&]() {
			MovementComponent* _mvComponent = GetComponent<MovementComponent>();

			sf::Vector2f _direction = _mvComponent->GetDirection();
			float _yMultiplier = 0.9f;
			float _xMultiplier = 1.4f;
			float _currentXVelocity = 0.f;

			if (currentJumpTimerIndex == 0)
			{
				currentYVelocity = maxYVelocity;
				_currentXVelocity = 1.f * _xMultiplier;
			}
			else
			{
				currentYVelocity = maxYVelocity / ((currentJumpTimerIndex / 12) + 1);
				_currentXVelocity = 1.f * _xMultiplier / ((currentJumpTimerIndex / 12) + 1);
			}

			if (currentYVelocity < 2)
				return;

			//std::cout << "Move Wall Jump" << std::endl;
			_mvComponent->Move(sf::Vector2f(static_cast<float>(wallJumpDirection) * _currentXVelocity, -currentYVelocity * _yMultiplier) * static_cast<float>(Game::GetInstance().GetSenseOfGravity()));
			currentJumpTimerIndex++;
			}, sf::seconds(0), true, true);

		return true;
	}

	bool Character::Bonk(const int _collisionSideBinary)
	{
		collisionSideBinBonkBuffer = _collisionSideBinary;

		if (Timer* _currentDashTimer = TimerManager::GetInstance().GetApproximately("DashTimer"))
		{
			_currentDashTimer->Stop();
		}

		StopAllJumps();

		currentJumpTimerIndex = 0;
		Timer* _bonkTimer = new Timer("JumpTimer", [&]() {
			MovementComponent* _mvComponent = GetComponent<MovementComponent>();

			sf::Vector2f _direction = _mvComponent->GetDirection();

			float _yMultiplier = 0.9f;
			float _xMultiplier = 1.4f;

			switch (collisionSideBinBonkBuffer)
			{
			case COLLIDE_NONE:
				break;
			case COLLIDE_LEFT:
				_yMultiplier = -_yMultiplier;
				_xMultiplier = -_xMultiplier;
				break;
			case COLLIDE_RIGHT:
				_yMultiplier = _yMultiplier;
				_xMultiplier = _xMultiplier;
				break;
			case COLLIDE_UP:
				_yMultiplier = -_yMultiplier;
				_xMultiplier = 0.f;
				break;
			case COLLIDE_DOWN:
				_yMultiplier = _yMultiplier;
				_xMultiplier = 0.f;
				break;
			default:
				break;
			}

			float _currentYVelocity = 1.f * _yMultiplier * maxYVelocity / ((currentJumpTimerIndex / 12) + 1);
			float _currentXVelocity = 1.f * _xMultiplier / ((currentJumpTimerIndex / 12) + 1);


			if (std::abs(_currentYVelocity) < 2) return;

			//std::cout << "Move Bonk" << std::endl;
			_mvComponent->Move(sf::Vector2f(_currentXVelocity, -currentYVelocity * _yMultiplier) * static_cast<float>(Game::GetInstance().GetSenseOfGravity()));
			currentJumpTimerIndex++;
			}, sf::seconds(0), true, true);
		return false;
	}

	bool Character::Dash(const sf::Event& _event)
	{
		sf::Keyboard::Key _dashKey = sf::Keyboard::C;
		if (_event.type == sf::Event::JoystickButtonPressed && _event.joystickButton.button != 2)return false;
		if (_event.type == sf::Event::KeyPressed && _event.key.code != _dashKey)return false;

		if (dashCount <= 0) return false;
		isDashing = true;
		dashCount--;
		currentDashTimerIndex = 0;

		sf::Keyboard::Key _up = sf::Keyboard::Z;
		sf::Keyboard::Key _left = sf::Keyboard::Q;
		sf::Keyboard::Key _down = sf::Keyboard::S;
		sf::Keyboard::Key _right = sf::Keyboard::D;

		MovementComponent* _mvComponent = GetComponent<MovementComponent>();
		sf::Vector2f _direction = _mvComponent->GetDirection();
		float _xDirectionModif = 0.f;

		if (_event.type == sf::Event::JoystickButtonPressed)
		{
			float _axisXPosition = sf::Joystick::getAxisPosition(0, sf::Joystick::X);
			float _axisYPosition = sf::Joystick::getAxisPosition(0, sf::Joystick::Y);
			int _xDirection = (_axisXPosition <= -DEAD_ZONE) ? -1 : _axisXPosition >= DEAD_ZONE ? 1 : 0;
			int _YDirection = (_axisYPosition <= -DEAD_ZONE) ? -1 : _axisYPosition >= DEAD_ZONE ? 1 : 0;
			dashDirectionBuffer = { _xDirection, _YDirection };
		}
		else
		{
			dashDirectionBuffer = { -static_cast<int>(sf::Keyboard::isKeyPressed(_left)) + sf::Keyboard::isKeyPressed(_right),
									-static_cast<int>(sf::Keyboard::isKeyPressed(_up)) + sf::Keyboard::isKeyPressed(_down) };
		}

		if (Timer* _currentDashTimer = TimerManager::GetInstance().GetApproximately("DashTimer"))
		{
			currentDashTimerIndex = 0;
			currentDashVelocity = maxDashVelocity;
			_currentDashTimer->Reset();
		}
		else
		{
			Timer* _dashTimer = new Timer("DashTimer", [&]() {
				MovementComponent* _mvComponent = GetComponent<MovementComponent>();

				currentDashVelocity = maxYVelocity / ((currentDashTimerIndex / 10) + 1);

				if (currentDashVelocity < 2) return;

				//std::cout << "Move Dash" << std::endl;
				_mvComponent->Move(sf::Vector2f(dashDirectionBuffer * currentDashVelocity), false);
				currentDashTimerIndex++;
				}, sf::seconds(0), true, true);

		}
		SoundManager::GetInstance().Play("dash_pink_left.wav");


		return true;
	}

	bool Character::Climb(const sf::Event& _event)
	{
		sf::Keyboard::Key _climbKey = sf::Keyboard::V;
		sf::Keyboard::Key _upKey = sf::Keyboard::Z;
		sf::Keyboard::Key _downKey = sf::Keyboard::S;

		if (_event.type == sf::Event::KeyPressed && _event.key.code != _climbKey && _event.key.code != _upKey && _event.key.code != _downKey)return false;

		if ((_event.type == sf::Event::JoystickMoved && sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::Z) >= 50)
			|| (_event.type == sf::Event::KeyPressed && _event.key.code == _climbKey) )
		{
			isClimbing = true;
		}

		else if ((_event.type == sf::Event::KeyReleased && _event.key.code == _climbKey) ||
			((_event.type == sf::Event::JoystickMoved) && sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::Z) <= 50))
		{
			MovementComponent* _mvComponent = GetComponent<MovementComponent>();
			isClimbing = false;
			_mvComponent->SetDirection({ _mvComponent->GetDirection().x, 0 });
		}

		CollisionInfos _collisionWWall = GetComponent<CollisionComponent>()->CheckCollision(true);
		if (!(_collisionWWall.entityTypeBinary & ENTITY_TILE) || (!(_collisionWWall.collisionSideBinary & COLLIDE_RIGHT) && !(_collisionWWall.collisionSideBinary & COLLIDE_LEFT))) isClimbing = false;
		if (!isClimbing) return false;
		StopAllJumps();



		MovementComponent* _mvComponent = GetComponent<MovementComponent>();
		sf::Vector2f _direction = _mvComponent->GetDirection();

		float _yDirection;
		if (_event.type == sf::Event::JoystickMoved)
		{
			float _axisYPosition = sf::Joystick::getAxisPosition(0, sf::Joystick::Y);
			_yDirection = (_axisYPosition <= -DEAD_ZONE) ? -1.f : _axisYPosition >= DEAD_ZONE ? 1.f : 0.f;
		}
		else
			_yDirection = -(sf::Keyboard::isKeyPressed(_upKey) * 1.f) + sf::Keyboard::isKeyPressed(_downKey) * 1.f;

		sf::Vector2f _newDirection(_direction.x, _yDirection);
		lastWallCollisionSide = GetComponent<CollisionComponent>()->CheckCollision(true).collisionSideBinary & COLLIDE_LEFT ? COLLIDE_LEFT : COLLIDE_RIGHT;

		_mvComponent->SetDirection(_newDirection);
		return true;
	}

	void Character::ResetJumpValues()
	{
		isJumping = true;
		currentJumpTimerIndex = 0;
	}

	void Character::ResetDashValues()
	{
		isDashing = false;
		currentDashTimerIndex = 0;
	}

	void Character::Update()
	{
		MovementComponent* _mvm = GetComponent<MovementComponent>();
		//std::cout << _mvm->GetDirection().x << " | " << _mvm->GetDirection().y << std::endl;

		// Climb
		if (isClimbing)
		{
			CollisionInfos _collisionWWall = GetComponent<CollisionComponent>()->CheckCollision(true);
			if (!(_collisionWWall.entityTypeBinary & ENTITY_TILE) || (!(_collisionWWall.collisionSideBinary & COLLIDE_RIGHT) && !(_collisionWWall.collisionSideBinary & COLLIDE_LEFT)))
			{
				isClimbing = false;
				MovementComponent* _mvComponent = GetComponent<MovementComponent>();
				/*_mvComponent->SetDirection({ _mvComponent->GetDirection().x, 0 });*/

				const float _senseOfGravity = static_cast<float>(Game::GetInstance().GetSenseOfGravity());
				if (lastWallCollisionSide & COLLIDE_RIGHT)
				{
					MovementComponent* _mvComponent = GetComponent<MovementComponent>();
					//std::cout << "Move Collion right climb" << std::endl;
					_mvComponent->Move(sf::Vector2f(-10, -10) * _senseOfGravity);
				}
				else if (lastWallCollisionSide & COLLIDE_LEFT)
				{
					//std::cout << "Move Collion left climb" << std::endl;
					MovementComponent* _mvComponent = GetComponent<MovementComponent>();
					_mvComponent->Move(sf::Vector2f(10, -10) * _senseOfGravity);
				}
			}
		}

	
		CollisionInfos _collisitions = GetComponent<CollisionComponent>()->CheckCollision();
		if (((_collisitions.collisionSideBinary & COLLIDE_UP) && (_collisitions.collisionSideBinary & COLLIDE_DOWN))|| ((_collisitions.collisionSideBinary & COLLIDE_LEFT) && (_collisitions.collisionSideBinary & COLLIDE_RIGHT))) {

			Die();
		}
	
		Entity::Update();
		if (isDead) {
			Respawn();
		}

	}

	void Character::Die()
	{
		RenderWindow& _window = Game::GetInstance().GetWindow();
		if (Timer* _dashTimer = TimerManager::GetInstance().GetApproximately("DashTimer"))
		{
			_dashTimer->Stop();
			ResetDashValues();
		}

		isDead = true;
		isJumping = false;
		isClimbing = false;
		isDashing = false;
	
		SoundManager::GetInstance().Play("death.wav");

	}


	void Character::Respawn()
	{
		shape->setPosition(checkPoint.x, checkPoint.y - (shape->getGlobalBounds().getSize().y - TILE_SIZE.y) / 2);
		Camera::GetInstance().Update(true);
		isDead = false;
		isJumping = false;
		isClimbing = false;
		isDashing = false;

	EntityManager::GetInstance().Reset();
	MovementComponent* _mv = GetComponent<MovementComponent>();
	_mv->SetCanMove(false);
	_mv->SetDirection({ 0.f,0.f });
	new Timer("RespawmMovement" + id, [this]() {GetComponent<MovementComponent>()->SetCanMove(true); }, seconds(0.2f));
	}

	
	
