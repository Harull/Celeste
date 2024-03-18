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
        if (!_soundData->loadFromFile("Assets/Songs/Sounds/"+_path))
		{
			cerr << "Le son n'a pas été correctement chargée !" << endl;
		}
	}
}

void SoundManager::Update()
{
    for (Sound* _sound : sounds) {
        if (_sound==nullptr ||!_sound->getStatus())
        {
            sounds.erase(remove(sounds.begin(), sounds.end(), _sound), sounds.end());
            delete _sound;
        }
    }
	
}
