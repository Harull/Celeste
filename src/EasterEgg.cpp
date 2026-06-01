#include "../include/EasterEgg.h"
#include "../include/Game.h"
#include "../include/Player.h"

EasterEgg::EasterEgg(const Vector2f& _position, const Vector2f& _size, Grid* _owner, const string& _path)
	:Tile(ENTITY_STRAWBERRY, _position, _size, _path, _owner)
{
	components.push_back(new AnimationComponent(
		this, _path,
		{ AnimationData("IdleEasterEgg", Vector2f(0.0f,0.0f), Vector2f(120.0f, 150.0f), READ_RIGHT, ANIM_DIR_NONE, true, 7, 0.1f) },
		ANIM_DIR_NONE
	));
	collisionReaction = [this](int _collisionSide, int _collisionSideBinary) {GetHit(_collisionSideBinary); };
	isTangible = false;
	isUsed = false;
	otherWindow = nullptr;
}

EasterEgg::~EasterEgg()
{
	delete otherWindow;
}

void EasterEgg::GetHit(int _collisionSideBinary)
{
	if (_collisionSideBinary != ENTITY_CHARACTER)return;
	if (isUsed)return;
	isUsed = true;
	shape->setFillColor(Color::Transparent);
	GetComponent<AnimationComponent>()->Finish();
	otherWindow = new OtherWindow();
	otherWindow->Run();
}
