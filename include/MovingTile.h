#pragma once
#include"Tile.h"
#include"MovementComponent.h"
class MovingTile :public Tile
{
	vector<Vector2f>destination;
	Vector2f currentDestination;
	int indexDestination;
	bool activated;

	float yeetMultiplier;
	int currentYeetTimerIndex;
	sf::Clock timeSinceDestination;
	bool isYeeted;
	sf::Vector2f dirWithVelocity;
	sf::Vector2f previousNonNullDirection;
	sf::Vector2f yeetFinalMove;

public:
	void UpdateDirection()
	{
		currentDestination = destination[indexDestination];
		MovementComponent* _move = GetComponent<MovementComponent>();
		Vector2f _direction = _move->GetDirectionByPositions(currentDestination);
		_move->SetDirection(_direction * 8.0f); 
	}
	void AddDestination(const Vector2f& _destination)
	{
		destination.push_back(_destination);
	}
public:
	MovingTile(const EntityType _type, const Vector2f& _position, const Vector2f& _size, const string& _path, Grid* _owner);

private:
	void CarryCharacter();
	void YeetCharacter(const bool _fromPreviousLocation = false);
	bool TryYeetCharater();
	void Move(int _collisionSide, int _collisionSideBinary);

	virtual void Update()override;
	virtual void Reset()override;
};

