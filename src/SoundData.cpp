#include "../include/SoundData.h"
#include "../include/SoundManager.h"

SoundData::SoundData(const string& _path) : IManageable(_path)
{
	Register();
}

void SoundData::Register()
{
	SoundManager::GetInstance().Add(id, this);
}