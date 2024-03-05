#pragma once
#include <SFML/Graphics.hpp>
#include "Map.h"
#include "Player.h"
#include "Singleton.h"
#include "Menu.h"
#include "FirstMenu.h"
#include "MusicManager.h"
#include "Snow.h"
#include "Macro.h"

using namespace sf;

enum SenseOfGravity
{
	GRAVITY_INVERTED = -1, GRAVITY_NORMAL = 1
};

class Game : public Singleton<Game>
{
	RenderWindow window;
	Map* map;
	Player* player;
	FloatRect visibleArea;
	Menu* menu;
	MusicManager* musicManager;

	Snow* snow;
	sf::Clock clock;
	float dt;

	SenseOfGravity senseOfGravity;

public:
	Map* GetMap()
	{
		return map;
	}
	Vector2u GetWindowSize()
	{
		return window.getSize();
	}
	Player* GetPlayer()
	{
		return player;
	}
	RenderWindow& GetWindow() {
		return window;
	}
	SenseOfGravity GetSenseOfGravity()const
	{
		return senseOfGravity;
	}
	void ToggleSenseOfGravity()
	{
		senseOfGravity = static_cast<SenseOfGravity>(static_cast<int>(senseOfGravity) * -1);
		std::vector<Animation*> _vectorOfAnims = player->GetCharacter()->GetComponent<AnimationComponent>()->GetAllValues();
		for (Animation* _anims : _vectorOfAnims)
		{
			sf::Sprite* _sprite = _anims->GetSprite();
			_sprite->rotate(180);
		}
	}

public:
	Game();
	~Game();

public:
	void Launch();
	void UpdateWindow();
	void SelectLevel(const int _value);
	void Resume();

private:
	void Start();
	void Stop();
	void InitWindow();
	void InitMenu();
	void InitMap(const int _value);
	void InitInput();
	bool ShowOptionsInGame(const Event& _event);
	void InitPlayer();
	void Update();
	void UpdateVisibleArea();
	void UpdateEvents();

public:
	void UpdateSnow();
};

