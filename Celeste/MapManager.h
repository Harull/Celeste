#pragma once
#include "Singleton.h"
#include "IManager.h"
#include "Map.h"
#include <map>

using namespace std;

class MapManager : public Singleton<MapManager>, public IManager<string, Map>
{
public:
    bool IsAvailable(const Vector2f& _position);
};