#include "Snowflake.h"

Snowflake::Snowflake(sf::Vector2f _position, float _speed) :
    position(_position), speed(_speed)
{
    shape = new CircleShape();
    float _randomRadius = static_cast<float>(rand() % 20 + 10);
    shape->setRadius(_randomRadius);

	TextureManager::GetInstance().Load(shape, "C:/Users/Kylia/Pictures/Meme/image.png");
}



Snowflake::Snowflake()
{
}


void Snowflake::update(float _dt) {
    position.y += speed * _dt;
    position.x -= speed * _dt;


    if (position.y > sf::VideoMode::getDesktopMode().height) {
        position.y = 0.f;
        position.x = static_cast<float>(rand() % static_cast<int>(sf::VideoMode::getDesktopMode().width));
    }

    if (position.x < 0.f) {
        position.x = static_cast<float>(sf::VideoMode::getDesktopMode().width);
    }
}

void Snowflake::draw(sf::RenderTarget& _target) {
    shape->setPosition(position);
    _target.draw(*shape);
}
