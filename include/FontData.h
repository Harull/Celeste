#pragma once

#include "IManageable.h"

#include <string>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class FontManager;

class FontData : public Font, public IManageable<string>
{

public:
	FontData(const string& _path);

public:
	virtual void Register() override;
};

