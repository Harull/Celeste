#include "Trap.h"

Trap::Trap(const string& _name, const Vector2f& _position, const Vector2f& _size, const string& _path) :
	Entity({ _name, _position, _size, _path })
{
}
