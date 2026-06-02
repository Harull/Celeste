#include "FontManager.h"

#include <iostream>

void FontManager::Load(Text* _text, const string& _path, const bool _isSmooth)
{
	FontData* _fontData = Get(_path);

	if (!_fontData)
	{
		_fontData = new FontData(_path);
		if (!_fontData->loadFromFile(_path))
		{
			cerr << "La police d'écriture n'a pas été correctement chargée !" << endl;
		}

		_fontData->setSmooth(_isSmooth);
	}

	_text->setFont(*_fontData);
}


