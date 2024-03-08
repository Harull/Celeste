#pragma once

#include "IManager.h"
#include "SoundData.h"
#include "Singleton.h"
#include<iostream>
using namespace std;


class SoundManager : public Singleton<SoundManager>, public IManager<string, SoundData>
{
    vector<Sound*> sounds;

public:
    SoundManager();
	~SoundManager();

private:
    void Load(const string& _path);

public:
    void Play(const string& _path, const float _volume = 10.0f);
};
