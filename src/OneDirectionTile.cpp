#include "../include/OneDirectionTile.h"
#include "../include/CollisionComponent.h"
#include "../include/TextureManager.h"

OneDirectionTile::OneDirectionTile(const EntityType _type, const Vector2f& _position, const Vector2f& _size, const string& _path, Grid* _owner) :Tile(_type, _position, _size, _path, _owner)
{
    isTangible = true;

	collisionReaction = [this](int _collisionSide, int _collisionSideBinary) {GetHit(_collisionSide, _collisionSideBinary); };
}

void OneDirectionTile::GetHit(int _collisionSide, int _collisionSideBinary)
{
    if (_collisionSideBinary == ENTITY_CHARACTER && !(_collisionSide & COLLIDE_UP))
        isTangible = false;
    else
        isTangible = true;
}
