#include "SoundManager.h"


SoundManager::SoundManager()
{
    sounds = vector<Sound*>();

}

SoundManager::~SoundManager()
{
	for (Sound* _sound : sounds)
	{
		delete _sound;
	}
}


void SoundManager::Play(const string& _path, const float _volume)
{
    if (_path == "") return;

    SoundData* _soundData = Get(_path);

    if (!_soundData)
    {
        Load(_path);
        _soundData = Get(_path);
    }

    if (_soundData)
    {
        Sound* _sound = new Sound();
        sounds.push_back(_sound);
        _sound->setBuffer(*_soundData);
        _sound->setVolume(_volume);
        _sound->play();

    }
}

void SoundManager::Load(const string& _path)
{
	if (_path == "") return;

	SoundData* _soundData = Get(_path);

	if (!_soundData)
	{
		_soundData = new SoundData(_path);
		if (!_soundData->loadFromFile(_path))
		{
			cerr << "Le son n'a pas été correctement chargée !" << endl;
		}
	}
}
