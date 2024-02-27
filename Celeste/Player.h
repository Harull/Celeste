#pragma once
#include "Character.h"

struct PlayerData
{
	int BerryCount;
	int deathCount;
};

class Player
{
	static PlayerData data;
	Character* character;

public:
	Player();
	~Player();

public:
	void Update();

	void InitInput();
};

