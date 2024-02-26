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
	Character* GetCharacter()
	{
		return character;
	}

	Shape* GetShape()
	{
		return character->GetShape();
	}

public:
	Player();

public:
	void Update();

	void InitInput();

};

