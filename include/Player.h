#pragma once
#include "Character.h"

struct PlayerData
{
	int strawBerrycount = 0;
	int BerryCount = 0;
	int deathCount = 0;

	void IncreaseStrawBerry()
	{
		strawBerrycount++;
	}
};

class Player
{
	PlayerData data;
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
	 PlayerData& GetPlayerData()
	{
		return data;
	}

public:
	Player();
	

public:
	void Update();
	void InitInput();
};

