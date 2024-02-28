#pragma once
#include <SFML/Audio.hpp>
#include "IManageable.h"
#include <iostream>

using namespace std;
using namespace sf;


class MusicData : public Music, public IManageable<string>
{

public:
	MusicData(const string& _id);

	void Play(const string& _path);
	// Hérité via IManagable
	void Register() override;
};
