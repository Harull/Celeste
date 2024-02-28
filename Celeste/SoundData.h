#pragma once
#include "IManageable.h"

#include <SFML/Audio.hpp>

using namespace sf;
using namespace std;

class SoundManager;

class SoundData : public SoundBuffer, public IManageable<string>
{

public:
	SoundData(const string& _path);

public:
	virtual void Register() override;
};