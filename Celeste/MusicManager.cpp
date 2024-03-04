#include "MusicManager.h"

void MusicManager::Play(const string& _path)
{

	if (_path == "") return;

	_musicData = Get(_path);

	if (!_musicData)
	{
		_musicData = new MusicData(_path);
		if (!_musicData->openFromFile("Assets/Songs/" + _path))
		{
			cerr << "Le son n'a pas été correctement chargée !" << endl;
			return;
		}
	}
	if (_musicData)
	{
		_musicData->play();
		_musicData->setVolume(100);
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
			cout << "Volume augmenté. Volume actuel: " << currentVolume << endl;
		}
		else
		{
			cout << "le son est deja a fond." << endl;
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
			cout << "Volume diminué. Volume actuel: " << currentVolume << endl;
		}
		else
		{
			cout << "le son est deja coupé." << endl;
		}
	}
}

void MusicManager::MuteVolume()
{
	_musicData->setVolume(0);
}

void MusicManager::UnmuteVolume(int _sound)
{
	_musicData->setVolume(static_cast<float>(_sound));
}

