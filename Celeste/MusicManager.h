#pragma once

#include "IManager.h"
#include "MusicData.h"
#include "Singleton.h"
#include<iostream>

using namespace std;

class MusicManager : public Singleton<MusicManager>, public IManager<string, MusicData>
{
	MusicData* _musicData;

public:
	void Play(const string& _path);
	void IncreaseVolume();
	void DecreaseVolume();
	void MuteVolume();
	void UnmuteVolume(const float _sound);
	void SetVolume(const float _volume);
};

