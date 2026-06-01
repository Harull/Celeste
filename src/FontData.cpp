#include "../include/FontData.h"
#include "../include/FontManager.h"

FontData::FontData(const string& _path) : IManageable(_path)
{
	Register();
}

void FontData::Register()
{
	FontManager::GetInstance().Add(id, this);
}
