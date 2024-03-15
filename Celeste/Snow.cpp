#include "Snow.h"
#include "Macro.h"

Snow::Snow(int _numFlakes, float _minSpeed, float _maxSpeed) :
    flakes(_numFlakes)
{
    for (int i = 0; i < _numFlakes; ++i) {
        float x = static_cast<float>(RandomMaxMin(static_cast<int>(sf::VideoMode::getDesktopMode().width)));
        float y = static_cast<float>(RandomMaxMin(static_cast<int>(sf::VideoMode::getDesktopMode().height)));
        float speed = (_minSpeed + static_cast<float>(rand()) / (RAND_MAX / (_maxSpeed - _minSpeed)));
        flakes[i] = Snowflake(sf::Vector2f(x, y), speed);
    }
}

void Snow::update(float _dt) {
    for (Snowflake& flake : flakes) {
        flake.update(_dt);
    }
}

void Snow::draw(sf::RenderTarget& _target) {
    for (Snowflake& flake : flakes) {
        flake.draw(_target);
    }
}
