#include "Camera.h"
#include"EntityManager.h"


void Camera::InitPosition()
{
	Vector2f _cameraPosition= Vector2f(-0.845f, -0.65f);
	

	const Vector2f& _cameraSize = Vector2f(2.0f, 2.0f);

	setViewport(FloatRect(_cameraPosition, _cameraSize));
}

void Camera::Init(const Vector2f& _from, const Vector2f& _to)
{
	setCenter(_from);
	setSize(_to);
	InitPosition();
}

void Camera::Update()
{
	const Vector2f& _currentPosition = getCenter();
	const Vector2f& _playerPosition = EntityManager::GetInstance().Get("Character")->GetPosition();

	Vector2f _offset = Vector2f(0.0f, 0.0f);
	_offset.x = _currentPosition.x > _playerPosition.x ? -0.1f : 0.1f;
	_offset.y = _currentPosition.y > _playerPosition.y ? -0.1f : 0.1f;

	move(_offset);
}
