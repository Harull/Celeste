#include "Character.h"
#include "TextureManager.h"

#define CHARACTER_TEXTURE ""

Character::Character(const sf::Vector2f _size, const sf::Vector2f _position, const bool _isVisible) 
	: Entity(EntityData("Character", _position, _size))
{
	//TODO envoyer la shape à l'entity
	components = std::vector<Component*>();
	isVisible = _isVisible;

	InitShape();
	InitComponents();

}

void Character::InitShape()
{
	TextureManager::GetInstance().Load(shape, CHARACTER_TEXTURE);
}

void Character::InitComponents()
{
	components.reserve(3);

	//TODO set Components

	/*components.emplace_back(new MovementComponent);
	components.emplace_back(new GravityComponent);*/
}
