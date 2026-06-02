#include "MusicManager.h"

void MusicManager::Play(const string& _path)
{
	if (musicData)
	{
		musicData->stop();
		delete musicData;
		musicData = nullptr;
	}

	if (_path == "") return;

	musicData = Get(_path);

	if (!musicData)
	{
		musicData = new MusicData(_path);
		if (!musicData->openFromFile("assets/Songs/Musics/" + _path))
		{
			cerr << "Le son n'a pas été correctement chargée !" << endl;
			return;
		}
	}
	if (musicData)
	{
		musicData->play();
		musicData->setVolume(volume);
	}
}

void MusicManager::IncreaseVolume()
{
	if (musicData)
	{
		if (volume < 110)
		{
			volume += 10;
			musicData->setVolume(volume);
		}

	}
}

void MusicManager::DecreaseVolume()
{
	if (musicData)
	{
		if (volume > 0)
		{
			volume -= 10;
			musicData->setVolume(volume);
		}

	}
}

void MusicManager::MuteVolume()
{
	volume = 0;
	musicData->setVolume(volume);
}

void MusicManager::UnmuteVolume(const float _sound)
{
	volume = _sound;
	musicData->setVolume(volume);
}

void MusicManager::SetVolume(const float _volume)
{
	volume = _volume;
	musicData->setVolume(volume);
}

