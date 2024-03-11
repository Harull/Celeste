#pragma once

#include "IManager.h"
#include "SoundData.h"
#include "Singleton.h"
#include<iostream>
using namespace std;


class SoundManager : public Singleton<SoundManager>, public IManager<string, SoundData>
{
    vector<Sound*> sounds;
	float volume = 10.0f;

public:
    SoundManager();
	~SoundManager();

private:
    void Load(const string& _path);
	void Update();

public:
    void Play(const string& _path);
	void SetVolume(const float _volume) {
		volume = _volume;
	}
	void MuteVolume() {
		volume = 0;
	}
};
