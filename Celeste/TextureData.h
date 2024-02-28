#pragma once
#include "IManageable.h"
#include <string>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class TextureManager;

class TextureData : public Texture, public IManageable<string>
{
	IntRect rect;

public:
	void SetRect(const IntRect& _rect)
	{
		rect = _rect;
	}
	IntRect GetRect() const
	{
		return rect;
	}
public:
	TextureData(const string& _path);

public:
	virtual void Register() override;
};


