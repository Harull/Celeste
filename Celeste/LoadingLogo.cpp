#include "LoadingLogo.h"
#include"AnimationComponent.h"
#include "Macro.h"
LoadingLogo::LoadingLogo( const Vector2f _position):Entity(EntityData("LoadingLogo",ENTITY_NONE, _position,Vector2f(50.f,50.f) ))
{
	components.push_back(new AnimationComponent(this, "Assets/Fraise.png", { AnimationData(S_APPEND("loadingStrawberry"), Vector2f(0.0f,0.0f), Vector2f(120.42f, 150.0f), READ_RIGHT, ANIM_DIR_NONE, true, 7, 0.1f) },
		ANIM_DIR_NONE
	));
}
