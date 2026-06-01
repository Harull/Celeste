#pragma once

#include "IManager.h"
#include "FontData.h"
#include "Singleton.h"


class FontManager : public Singleton<FontManager>, public IManager<string, FontData>
{
public:
	void Load(Text* _text, const string& _path, const bool _isSmooth = true);
};

