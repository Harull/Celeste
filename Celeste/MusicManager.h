#pragma once

#include "IManager.h"
#include "MusicData.h"
#include "Singleton.h"

class MusicManager : public Singleton<MusicManager>, public IManager<string, MusicData>
{

public:
	void Play(const string& _path);
};


