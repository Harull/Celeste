#include "FragileTile.h"
#include"CollisionComponent.h"
#include"TimerManager.h"
FragileTile::FragileTile(const EntityType _type, const Vector2f& _position, const Vector2f& _size, const string& _path):Tile(_type,_position,_size,_path)
{
	components.push_back(new CollisionComponent(this, [this](int _collisionSide) {GetHit(_collisionSide); }));
}

void FragileTile::GetHit(int _collisionSide)
{
	if (_collisionSide != COLLIDE_UP)return;
	
	if (TimerManager::GetInstance().Get("TimerDestroy" + id))return;
	
	new Timer("TimerDestroy" + id,
		[this]() {shape->setFillColor(Color::Transparent);
	destroying = true;
		new Timer("TimerRespawn" + id, [this]() {
			Color _color = shape->getFillColor();
			_color.a = 100;
			shape->setFillColor(_color);
			destroying = false; }, seconds(5));
		}, seconds(2));



	
}
