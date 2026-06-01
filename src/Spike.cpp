#include "../include/Spike.h"
#include "../include/CollisionComponent.h"
#include "../include/TextureManager.h"
#include "../include/TimerManager.h"
#include "../include/EntityManager.h"

#define PATH_FRAGILE_TILE "../../../../assets/Snow1.png"


Spike::Spike( const Vector2f& _position, const Vector2f& _size, const string& _path, const EntityType& _type, Grid* _owner)
	: Trap( _position, _size, _path, _type, _owner)
{
	collisionReaction = [this](int _collisionSide, int _collisionSideBinary) {GetHit(_collisionSide, _collisionSideBinary); };
}

void Spike::GetHit(int _collisionSide, int _collisionSideBinary) {
	if (_collisionSideBinary != ENTITY_CHARACTER) return;
	Character* _hero = Game::GetInstance().GetPlayer()->GetCharacter();
	_hero->Die();
}

