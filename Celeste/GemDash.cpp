#include "GemDash.h"
#include "Game.h"
#include "Player.h"
#include "TextureManager.h"
#include "Game.h"
#include "SoundManager.h"
#include "TimerManager.h";

#define PATH_GEM "Assets/Gem.png"


GemDash::GemDash(const Vector2f& _position, const Vector2f& _size, const string& _path)
	:Tile(ENTITY_STRAWBERRY, _position, _size, _path)
{
	components.push_back(new AnimationComponent(
		this, _path,
		{ AnimationData("Gem", Vector2f(0.0f,0.0f), Vector2f(178.0f, 278.0f), READ_RIGHT, ANIM_DIR_NONE, true, 92, 0.01f) },
		ANIM_DIR_NONE
	));
	collisionReaction = [this](int _collisionSide, int _collisionSideBinary) {GetHit(_collisionSideBinary); };
	isUsed = false;
	isTangible = false;
}

void GemDash::GetHit(int _collisionSideBinary)
{
	if (_collisionSideBinary != ENTITY_CHARACTER)return;
	if (isUsed)return;
	GetComponent<AnimationComponent>()->Finish();
	isUsed = true;

	Character* _currentCharacter = Game::GetInstance().GetPlayer()->GetCharacter();
	_currentCharacter->SetDashCount(_currentCharacter->GetMaxDashCount());
	SoundManager::GetInstance().Play("diamond_touch.wav", 5.0f);

	new Timer("TimerDestroy" + id,
		[this]() {
			new Timer("TimerRespawn" + id, [this]() {
				isUsed = false;
				GetComponent<AnimationComponent>()->Restart();
				SoundManager::GetInstance().Play("diamond_return.wav", 5.0f);
				}, seconds(2));
		}, seconds(2));
}

void GemDash::Reset()
{
	isUsed = false;
	GetComponent<AnimationComponent>()->Restart();
	if (Timer* _timer= TimerManager::GetInstance().GetApproximately("TimerDestroy" + id) )
	{
		_timer->SetToRemove(true);
	}
}
