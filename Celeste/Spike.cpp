#include "Spike.h"
#include"CollisionComponent.h"
#include "TextureManager.h"
#include"TimerManager.h"
#include"EntityManager.h"

#define PATH_FRAGILE_TILE "Assets/Snow1.png"


Spike::Spike( const Vector2f& _position, const Vector2f& _size, const string& _path, const EntityType& _type)
	: Trap( _position, _size, _path, _type)
{
	collisionReaction = [this](int _collisionSide, int _collisionSideBinary) {GetHit(_collisionSide, _collisionSideBinary); };
}

void Spike::GetHit(int _collisionSide, int _collisionSideBinary) {
	Character* _hero = Game::GetInstance().GetPlayer()->GetCharacter();
	_hero->Die();
	cout << "Die"<<endl;
}

