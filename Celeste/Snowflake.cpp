#include "Snowflake.h"

Snowflake::Snowflake(sf::Vector2f position, float speed) :
    position(position), speed(speed)
{
    float randomRadius = static_cast<float>(rand() % 5 + 1);
    shape.setRadius(randomRadius);
    shape.setFillColor(sf::Color::White);
}

Snowflake::Snowflake()
{
}

void Snowflake::update(float dt) {
    position.y += speed * dt;
    position.x -= speed * dt;


    if (position.y > sf::VideoMode::getDesktopMode().height) {
        position.y = 0.f;
        position.x = static_cast<float>(rand() % static_cast<int>(sf::VideoMode::getDesktopMode().width));
    }
}

void Snowflake::draw(sf::RenderTarget& target) {
    shape.setPosition(position);
    target.draw(shape);
}
