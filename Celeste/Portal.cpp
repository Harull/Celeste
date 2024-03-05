#include "Portal.h"
#include"AnimationComponent.h"

#define PATH_PORTAL "Assets/portal.png"

Portal::Portal(Vector2f _position, Vector2f _size):Entity(EntityData("Portal",ENTITY_NONE, _position, _size))
{
	AnimationComponent* _anim = new AnimationComponent(this, PATH_PORTAL, {
		AnimationData("Standby",{0.f,25.f},{128.125f,95.f},READ_RIGHT,ANIM_DIR_STANDBY,true,8,0.1f),
		AnimationData("Appear",{0.f,154.f},{128.125f,95.f},READ_RIGHT,ANIM_DIR_APPEARS,false,8,0.1f,ANIM_DIR_STANDBY),
		AnimationData("Disappear",{0.f,285.f},{128.125f,95.f},READ_RIGHT,ANIM_DIR_DISAPPEARS,false,8,0.1f),
		}, ANIM_DIR_APPEARS);

	components.push_back(_anim);
}
