#include "SoundManager.h"


SoundManager::SoundManager()
{
    sounds = vector<Sound*>();
    volume = 2.0f;

}

SoundManager::~SoundManager()
{
	for (Sound* _sound : sounds)
	{
		delete _sound;
	}
}


void SoundManager::Play(const string& _path)
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
        _sound->setVolume(volume);
        _sound->play();

    }
    Update();
}

void SoundManager::Load(const string& _path)
{
	if (_path == "") return;

	SoundData* _soundData = Get(_path);

	if (!_soundData)
	{
		_soundData = new SoundData(_path);
        if (!_soundData->loadFromFile("assets/Songs/Sounds/" +_path))
		{
			cerr << "Le son n'a pas été correctement chargée !" << endl;
		}
	}
}

void SoundManager::Update()
{
    vector<Sound*> _toDelete = {};
    for (Sound* _sound : sounds) {
        if (_sound==nullptr ||!_sound->getStatus())
            _toDelete.push_back(_sound);
    }

    for (Sound* _soundToDel : _toDelete)
    {
        sounds.erase(remove(sounds.begin(), sounds.end(), _soundToDel), sounds.end());
        delete _soundToDel;
        _soundToDel = nullptr;
    }
	
}
