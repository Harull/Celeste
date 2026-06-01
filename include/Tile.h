#pragma once
#include "Entity.h"
#include <SFML/Graphics.hpp>
using namespace sf;
#include <string>
#include "Grid.h"
using namespace std;


class Tile : public Entity
{
protected:
	std::pair<int, int> index;
	Grid* owner;
	bool isMarkedByGetStackOfTypeArroundTile;

	bool isTangible;
	bool isShake;


public:


	void SetIsShake(const bool _status) {
		isShake = _status;
	}
	bool GetIsShake() const {
		return isShake;
	}

	bool GetIsTangible() const
	{
		return isTangible;
	}
	Shape* GetShape()
	{
		return shape;
	}
	void SetEntity(EntityType _type)
	{
		type = _type;
	}
	EntityType GetType() const { return type; }
	bool GetIsMarkedByGetStackOfTypeArroundTile()const
	{
		return isMarkedByGetStackOfTypeArroundTile;
		return isMarkedByGetStackOfTypeArroundTile;
	}
	void SetIsMarkedByGetStackOfTypeArroundTile(const bool _status)
	{
		isMarkedByGetStackOfTypeArroundTile = _status;
	}
public:
	Tile() = default;
	Tile(const EntityType _type, const Vector2f& _position, const Vector2f& _size, const string& _path, Grid* _owner);

public:
	template <typename Type>
	std::vector<Type*> GetStackOfTypeArround(const std::pair<int, int>& _index)
	{
		Tile* _concernedTile = owner->GetTiles()[_index.first][_index.second];

		std::vector<Type*> _sum;
		_concernedTile->SetIsMarkedByGetStackOfTypeArroundTile(true);

		for (int _i = 0; _i < 2; _i++)
		{
			for (int _j = 0; _j < 2; _j++)
			{
				std::pair<int, int> _modifiedIndex(_concernedTile->index);

				if (_i % 2 == 0)
					_modifiedIndex.first += ((_j % 2 == 0) ? -1 : 1);
				else
					_modifiedIndex.second += ((_j % 2 == 0) ? -1 : 1);

				if (owner->IsIndexValid(_modifiedIndex))
				{
					if (Type* _tile = dynamic_cast<Type*>(owner->GetTiles()[_modifiedIndex.first][_modifiedIndex.second]))
					{
						if (!_tile->GetIsMarkedByGetStackOfTypeArroundTile())
						{
							_sum.push_back(_tile);
							std::vector<Type*> _vectorToEmplace = GetStackOfTypeArround<Type>(_modifiedIndex);
							_sum.insert(_sum.end(), _vectorToEmplace.begin(), _vectorToEmplace.end());
						}
					}
				}
			}
		}
		return _sum;
	}

	template <typename Type>
	std::vector<Type*> GetStackOfTypeArround()
	{
		if (!owner->GetTiles()[this->index.first][this->index.second]) return std::vector<Type*>();
		std::vector<Type*> _toReturn = GetStackOfTypeArround<Type>(this->index);
		owner->ResetAllMarks();
		return _toReturn;
	}
};