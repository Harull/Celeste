#include "CheckPoint.h"
#include"EntityManager.h"
CheckPoint::CheckPoint(const EntityType _type, const Vector2f& _position, const Vector2f& _size, const string& _path):Tile(  _type,   _position,   _size,   _path)
{
	collisionReaction=[this](int _collisionSide, int _collisionSideBinary) {GetHit(_collisionSide, _collisionSideBinary); };
	shape->setFillColor(Color::Transparent);
	isTangible = false;
}

void CheckPoint::GetHit(int _collisionSide, int _collisionSideBinary)
{
	if (_collisionSideBinary != ENTITY_CHARACTER)return;
	Character* _hero = dynamic_cast<Character*>(EntityManager::GetInstance().Get("Character"));
	
	_hero->SetCheckPoint(GetPosition());
}
