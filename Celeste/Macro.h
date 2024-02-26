#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "EntityManager.h"
#include<Random>

using namespace std;
using namespace sf;

#define S_APPEND(name) name + GetUniqueId()

static void Normalize(Vector2f& _vector)
{
	// length = x * x + y * y
	const float _length = sqrtf(static_cast<float>(pow(_vector.x, 2) + pow(_vector.y, 2)));

	// normVec = vec / length
	_vector /= _length;
}

static string GetUniqueId()
{
	static int _id = 0;
	return to_string(_id++);
}

static void SetOriginAtMiddle(sf::Shape& _shape)
{
	_shape.setOrigin(_shape.getGlobalBounds().getSize() / 2.f);
}

template<class Class>
static vector<Class*> RetrieveAllAround(const Vector2f& _position, const int _tileAround)
{
	vector<Class*> _classes;

	/*   / const Vector2f & _size = MapManager::GetInstance().GetCurrent()->GetCellSize();
	   const Vector2f _offsets[] =
	   {
		   Vector2f(-1.0f, -1.0f),
		   Vector2f(-1.0f, 0.0f),
		   Vector2f(-1.0f, 1.0f),
		   Vector2f(0.0f, -1.0f),
		   Vector2f(0.0f, 0.0f),
		   Vector2f(0.0f, 1.0f),
		   Vector2f(1.0f, -1.0f),
		   Vector2f(1.0f, 0.0f),
		   Vector2f(1.0f, 1.0f),
	   };
	   Entity _entity = nullptr;

	   for (const Vector2f& _offset : _offsets)
	   {
		   const Vector2f& _rect = Vector2f(_position.x + _offset.x * _size.x * _tileAround,
			   _position.y + _offset.y * _size.y * _tileAround);

		   if (!MapManager::GetInstance().GetCurrent()->IsAvailable(_rect, _entity))
		   {
			   if (_entity)
			   {
				   if (Class* _class = dynamic_cast<Class>(_entity))
				   {
					   _classes.push_back(_class);
				   }
			   }
		   }
	   } /*/

	return _classes;
}


static bool IsNearlyEqual(const Vector2f& _first, const Vector2f& _second)
{
	return abs(_first.x - _second.x) < 0.5f && abs(_first.y - _second.y) < 0.5f;
}

template<typename Class>
static vector<Class*> RetrieveAllEnemiesAround(const Vector2f& _position, const float _radiusAction)
{
	/*vector<Class*> _classes = vector<Class*>();
	CircleShape* _circle = new CircleShape(_radiusAction);
	_circle->setPosition(_position);
	const vector<Entity*> _entities = EntityManager::GetInstance().GetAllValues();
	for (Entity* _entity : _entities)
	{
		if (_circle->getGlobalBounds().intersects(_entity->GetShape()->getGlobalBounds()))
		{
			Class* _class = dynamic_cast<Class*>(_entity);
			_classes.push_back(_class);
		}
	}

	return _classes;*/
}


static int RandomMaxMin(const int _max, const int _min = 0)
{
	if (_max < _min)
	{
		std::cerr << "RandomMaxMin's values are inverted, value returned: 0" << std::endl;
		return 0;
	}
	std::mt19937 _rng(std::random_device{}());
	std::uniform_int_distribution<int> _distribution(_min, _max);
	return _distribution(_rng);
}

template<typename T>
T* GetRandomItemInVector(std::vector<T*>& _vectorConcerned)
{
	if (_vectorConcerned.empty()) return nullptr;
	const int _arraySize = static_cast<int> (_vectorConcerned.size());
	return _vectorConcerned[RandomMaxMin(_arraySize - 1)];
}

template<typename T>
void DeleteVectorWParamPointer(std::vector<T>& _vect)
{
	for (auto _vToDelete : _vect)
	{
		delete _vToDelete;
		_vToDelete = nullptr;
	}
}
