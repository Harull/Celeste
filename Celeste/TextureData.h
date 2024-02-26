#pragma once
#include "IManageable.h"
#include <string>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class TextureManager;

class TextureData : public Texture, public IManageable<string>
{

public:
	TextureData(const string& _path);

public:
	virtual void Register() override;
};


