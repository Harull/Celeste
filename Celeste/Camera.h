#pragma once
#include<SFML/Graphics.hpp>
#include"Singleton.h"

using namespace sf;
class Camera: public View, public Singleton<Camera>
{

	
private:
	
	void InitPosition();
public:
	void Init(const Vector2f& _from, const Vector2f& _to);
	void Update();
	
};

