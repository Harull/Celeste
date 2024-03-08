#pragma once
#include<SFML/Graphics.hpp>
#include"Singleton.h"

using namespace sf;
class Game;


class Camera: public View, public Singleton<Camera>
{
	sf::Vector2i previousIndexes;
public:
	void Init(const Vector2f& _position, const Vector2f& _size);
	void Update(bool _heroTeleport =false);
	
};

