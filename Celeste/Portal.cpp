#include "Portal.h"
#include"AnimationComponent.h"
#include"Game.h"
#include"Macro.h"
#include"MovementComponent.h"
#include "SoundManager.h"


#define PATH_PORTAL "Assets/portal.png"

Portal::Portal(Vector2f _position, Vector2f _size) :Entity(EntityData("Portal", ENTITY_NONE, { _position.x - _size.x / 8.f,_position.y }, { _size.x * 2,_size.y }))
{
	AnimationComponent* _anim = new AnimationComponent(this, PATH_PORTAL, {
		AnimationData("Appear",{0.f,154.f},{128.125f,95.f},READ_RIGHT,ANIM_DIR_APPEARS,false,8,0.18f, ANIM_DIR_STANDBY),
		AnimationData("Standby",{0.f,25.f},{128.125f,95.f},READ_RIGHT,ANIM_DIR_STANDBY,false,8,0.18f, ANIM_DIR_DISAPPEARS),
		AnimationData("Disappear",{0.f,285.f},{128.125f,95.f},READ_RIGHT,ANIM_DIR_DISAPPEARS,false,8,0.1f,ANIM_DIR_INVICIBLE),
		AnimationData("none",{0.f,0.f},{0.f,00.f},READ_RIGHT,ANIM_DIR_INVICIBLE,true,8,0.1f),
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
		for (SmallMap* _map : _maps)
		{
			for (Vector2f _position : _map->GetGrid()->GetPositionsTileEmpty())
			{
				validPos = true;
				for (Tile* _tile : _map->GetGrid()->GetTilesMap())
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

	destination = GetRandomItemInVector(_emptyTiles);

}

void Portal::Teleport()
{
	new Timer("Teleport player", [this]() {

		shape->setPosition({ destination.x + shape->getGlobalBounds().getSize().x / 8.f,destination.y });

		Character* _player = Game::GetInstance().GetPlayer()->GetCharacter();
		_player->GetShape()->setPosition(destination);

		new Timer("free player", [this]() {Character* _player = Game::GetInstance().GetPlayer()->GetCharacter();
		_player->GetComponent< MovementComponent>()->SetCanMove(true); 
			}, seconds(2));

		new Timer("animOut player", [this]() {Character* _player = Game::GetInstance().GetPlayer()->GetCharacter();
		_player->GetComponent<AnimationComponent>()->SetDirection(ANIM_DIR_OUT_PORTAL);
		_player->GetComponent<AnimationComponent>()->Refresh();
			}, seconds(1.2));

		GetComponent<AnimationComponent>()->SetDirection(ANIM_DIR_APPEARS);
		GetComponent<AnimationComponent>()->Refresh();
		}, seconds(5));
}
