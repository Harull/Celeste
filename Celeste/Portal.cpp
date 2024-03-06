#include "Portal.h"
#include"AnimationComponent.h"
#include"Game.h"
#include"Macro.h"
#include"MovementComponent.h"


#define PATH_PORTAL "Assets/portal.png"

Portal::Portal(Vector2f _position, Vector2f _size) :Entity(EntityData("Portal", ENTITY_NONE, { _position.x+_size.x/2,_position.y }, { _size.x * 2,_size.y }))
{
	AnimationComponent* _anim = new AnimationComponent(this, PATH_PORTAL, {
		AnimationData("Standby",{0.f,25.f},{128.125f,95.f},READ_RIGHT,ANIM_DIR_STANDBY,false,8,0.1f,ANIM_DIR_DISAPPEARS),
		AnimationData("Appear",{0.f,154.f},{128.125f,95.f},READ_RIGHT,ANIM_DIR_APPEARS,false,8,0.1f,ANIM_DIR_STANDBY),
		AnimationData("Disappear",{0.f,285.f},{128.125f,95.f},READ_RIGHT,ANIM_DIR_DISAPPEARS,false,8,0.1f),
		}, ANIM_DIR_APPEARS);

	components.push_back(_anim);
	InitDestination();
}

void Portal::InitDestination()
{
	bool validPos;
	vector<Vector2f> _emptyTiles = vector<Vector2f>();
	for (vector<SmallMap*> _maps : Game::GetInstance().GetMap()->GetMaps())
	{
		for (SmallMap* _map :_maps)
		{
			for (Vector2f _position : _map->GetGrid()->GetPositionsTileEmpty())
			{
				validPos = true;
				for (Tile* _tile:_map->GetGrid()->GetTilesMap())
				{
					if (!_tile)continue;
					if (_tile->GetShape()->getGlobalBounds().contains({ _position.x,_position.y + _map->GetGrid()->GetTileSize().y }))
					{
						validPos = false;
					}
					else if (_tile->GetShape()->getGlobalBounds().contains({ _position.x,_position.y - _map->GetGrid()->GetTileSize().y }))
					{
						validPos = false;
					}
				}
				if (validPos)
				{
					_emptyTiles.push_back(_position);
				}
			}
			
			

		}
	}

	destination=GetRandomItemInVector(_emptyTiles);

}

void Portal::Teleport()
{
	
	new Timer("Teleport player", [this]() {shape->setPosition(destination);
		Character* _player=Game::GetInstance().GetPlayer()->GetCharacter();
	_player->GetShape()->setPosition(destination);
	_player->GetComponent< MovementComponent>()->SetCanMove(true);
	
	GetComponent<AnimationComponent>()->SetDirection(ANIM_DIR_APPEARS);
	GetComponent<AnimationComponent>()->Restart();
		}, seconds(3));
}
