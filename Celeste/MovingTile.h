#pragma once
#include"Tile.h"
#include"MovementComponent.h"
class MovingTile :public Tile
{
	vector<Vector2f>destination;
	Vector2f currentDestination;
	int indexDestination;
	bool activated;
public:
	void UpdateDirection()
	{
		currentDestination = destination[indexDestination];
		MovementComponent* _move = GetComponent<MovementComponent>();
		Vector2f _direction = _move->GetDirectionByPositions(currentDestination);
		_move->SetDirection(_direction);
	}
	void AddDestination(Vector2f _destination)
	{
		destination.push_back(_destination);
	}
public:
	MovingTile(const EntityType _type, const Vector2f& _position, const Vector2f& _size, const string& _path);

private:
	void CarryCharacter();
	void Move(int _collisionSide, int _collisionSideBinary);

	virtual void Update()override;
};

