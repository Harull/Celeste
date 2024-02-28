#pragma once

#include "IManager.h"
#include "MusicData.h"
#include "Singleton.h"
#include<iostream>

using namespace std;

class MusicManager : public Singleton<MusicManager>, public IManager<string, MusicData>
{

public:
	void Play(const string& _path);
};

