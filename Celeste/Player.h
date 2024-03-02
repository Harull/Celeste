#pragma once
#include "Character.h"

struct PlayerData
{
	int strawBerrycount;
	int BerryCount;
	int deathCount;

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
	~Player();

public:
	void Update();
	void InitInput();
};

