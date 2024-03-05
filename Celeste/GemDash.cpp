#include "GemDash.h"
#include "Game.h"
#include "Player.h"
#include "TextureManager.h"
#include "Game.h"

#define PATH_GEM "Assets/Gem.png"


GemDash::GemDash(const Vector2f& _position, const Vector2f& _size, const string& _path)
	:Tile(ENTITY_STRAWBERRY, _position, _size, _path)
{
	components.push_back(new AnimationComponent(
		this, _path,
		{ AnimationData("Gem", Vector2f(0.0f,0.0f), Vector2f(199.0f, 311.0f), READ_RIGHT, ANIM_DIR_NONE, true, 92, 0.01f) },
		ANIM_DIR_NONE
	));
	collisionReaction = [this](int _collisionSide, int _collisionSideBinary) {GetHit(_collisionSideBinary); };
	use = false;
}

void GemDash::GetHit(int _collisionSideBinary)
{
	if (_collisionSideBinary != ENTITY_CHARACTER)return;
	if (use)return;
	tangible = false;
	GetComponent<AnimationComponent>()->Finish();
	shape->setFillColor(Color::Transparent);

	new Timer("TimerDestroy" + id,
		[this]() {

			tangible = false;
			new Timer("TimerRespawn" + id, [this]() {
				GetComponent<AnimationComponent>()->Restart();
				tangible = true;
				}, seconds(2));
		}, seconds(2));
	Game::GetInstance().GetPlayer()->GetCharacter()->SetDashCount(1);
}
