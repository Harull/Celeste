#include "../include/LoadingLogo.h"
#include "../include/AnimationComponent.h"
#include "../include/Macro.h"

LoadingLogo::LoadingLogo( const Vector2f _position)
	: Entity(EntityData("LoadingLogo",ENTITY_NONE, _position,Vector2f(75.f,75.f) ))
{
	components.push_back(new AnimationComponent(this, "../../../../assets/Loading.png", { AnimationData(S_APPEND("LoadingIcon"), Vector2f(0.0f,0.0f), Vector2f(172.f, 172.0f), READ_RIGHT, ANIM_DIR_APPEARS, false, 6, 0.1f,ANIM_DIR_STANDBY),
		AnimationData(S_APPEND("LoadingIcon"), Vector2f(0.0f,172.0f), Vector2f(172.f, 172.0f), READ_RIGHT, ANIM_DIR_DISAPPEARS, false, 6, 0.1f,ANIM_DIR_NONE),
		AnimationData(S_APPEND("LoadingIcon"), Vector2f(0.0f,344.0f), Vector2f(172.f, 172.0f), READ_RIGHT, ANIM_DIR_STANDBY, true, 4, 0.1f),
		AnimationData(S_APPEND("LoadingIcon"), Vector2f(0.0f,344.0f), Vector2f(0.f, 0.f), READ_RIGHT, ANIM_DIR_NONE, true, 1, 0.1f)

		}, ANIM_DIR_APPEARS));

	new Timer(id, [this]() {GetComponent<AnimationComponent>()->SetDirection(ANIM_DIR_DISAPPEARS); }, seconds(2.0f));
}
