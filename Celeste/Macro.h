#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <Random>

using namespace std;
using namespace sf;

#define S_APPEND(name) name + GetUniqueId()



static bool Contain(const std::string& _id, const std::string& _value)
{
	if (_id.find(_value) != std::string::npos)
	{
		return true;
	}
	return false;
}

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

static void SetOriginAtMiddle(sf::Text& _text) {
	_text.setOrigin(_text.getLocalBounds().getSize() / 2.f);
}

static void SetOriginAtMiddle(sf::Sprite* _sprite)
{
	_sprite->setOrigin(_sprite->getLocalBounds().getSize() / 2.f);
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

static bool IsNearlyEqual(const float _first, const float _second)
{
	return abs(_first - _second) < 0.5f && abs(_first - _second) < 0.5f;
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
T GetRandomItemInVector(std::vector<T>& _vectorConcerned)
{
	if (_vectorConcerned.empty()) return T ();
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

template <typename Type>
static void SetOriginCentered(Type* _element)
{
	_element->setOrigin(_element->getGlobalBounds().getSize() / 2.0f);
}



template <typename Type>
static void Fade(Type* _value, const unsigned int _alpha)
{
	_value->setFillColor(sf::Color(255, 255, 255, _alpha));
}

template <typename Type>
static void FadeOutlineColor(Type* _value, const unsigned int _alpha)
{
	_value->setOutlineColor(sf::Color(0, 0, 0, _alpha));
}

template <typename Type>
static void MultiFade(std::vector<Type*> _values, const unsigned int _alpha)
{
	for (auto _value : _values)
	{
		_value->setFillColor(sf::Color(255, 255, 255, _alpha));
	}
}

static float Distance(const Vector2f& _first, const Vector2f& _second)
{
	return sqrtf(pow(_second.x - _first.x, 2.0f) + pow(_second.y - _first.y, 2.0f));
}


static void ModifyIntBetweenChevrons(const int _value, Text* _text) {

	string _textCopy = _text->getString();

	size_t _startBracketPos = _textCopy.find_first_of('<');

	size_t _endBracketPos = _textCopy.find_first_of('>', _startBracketPos);

	if (_startBracketPos != string::npos && _endBracketPos != string::npos && _endBracketPos > _startBracketPos) {
		string _valueBetweenBrackets = _textCopy.substr(_startBracketPos + 1, _endBracketPos - _startBracketPos - 1);
		
		int _valueChanged = std::stoi(_valueBetweenBrackets);
		_valueChanged = _value;

		_textCopy.replace(_startBracketPos + 1, _endBracketPos - _startBracketPos - 1, to_string(_valueChanged));

		_text->setString(_textCopy);
	}
}


template <typename T>
static void ShakeBlocks(vector<T*> _shapes) {
	vector<Vector2f> _origin;
	for (auto _shape : _shapes) {
		_origin.push_back(_shape->GetShape()->getPosition());
	}
	for (auto _shape : _shapes) {
		_shape->GetShape()->setPosition(Vector2f(_origin[RandomMaxMin(_origin.size() - 1)].x + RandomMaxMin(10, -10), _origin[RandomMaxMin(_origin.size() - 1)].y + RandomMaxMin(10, -10)));
	}
	int _i = 0;
	for (auto _shape : _shapes) {
		_shape->GetShape()->setPosition(_origin[_i]);
		_i++;
	}

}
