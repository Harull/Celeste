#pragma once
#include "UiManager.h"

class Hud
{
	Vector2f windowSize;
public:
	Hud();

	void InitMainMenu();
	void InitParamMenu();
	void CloseWithId(const vector<string>& _ids);
	void CloseAll();
	void CloseAllText();
};

