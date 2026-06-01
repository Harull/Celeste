#include "../include/TextureData.h"
#include "../include/TextureManager.h"

TextureData::TextureData(const string& _path) : IManageable(_path)
{
	Register();
}

void TextureData::Register()
{

	TextureManager::GetInstance().Add(id, this);
}
