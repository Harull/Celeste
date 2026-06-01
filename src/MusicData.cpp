#include "../include/MusicData.h"
#include "../include/MusicManager.h"
MusicData::MusicData(const string& _path) :IManageable(_path)
{
}

void MusicData::Register()
{
	MusicManager::GetInstance().Add(id, this);
}
