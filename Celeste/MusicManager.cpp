#include "MusicManager.h"

void MusicManager::Play(const string& _path)
{
	if (_musicData)
	{
		_musicData->stop();
		delete _musicData;
		_musicData = nullptr;
	}

	if (_path == "") return;

	_musicData = Get(_path);

	if (!_musicData)
	{
		_musicData = new MusicData(_path);
		if (!_musicData->openFromFile("Assets/Songs/Musics/" + _path))
		{
			cerr << "Le son n'a pas été correctement chargée !" << endl;
			return;
		}
	}
	if (_musicData)
	{
		_musicData->play();
		_musicData->setVolume(20);
	}
}

void MusicManager::IncreaseVolume()
{
	if (_musicData)
	{
		float currentVolume = _musicData->getVolume();
		if (currentVolume < 110)
		{
			currentVolume += 10; 
			_musicData->setVolume(currentVolume);
		}

	}
}

void MusicManager::DecreaseVolume()
{
	if (_musicData)
	{
		float currentVolume = _musicData->getVolume();
		if (currentVolume > 0)
		{
			currentVolume -= 10; 
			_musicData->setVolume(currentVolume);
		}

	}
}

void MusicManager::MuteVolume()
{
	_musicData->setVolume(0);
}

void MusicManager::UnmuteVolume(const float _sound)
{
	_musicData->setVolume(_sound);
}

void MusicManager::SetVolume(const float _volume)
{
	_musicData->setVolume(_volume);
}

