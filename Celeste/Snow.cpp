#include "Snow.h"
#include "Macro.h"

Snow::Snow(int numFlakes, float minSpeed, float maxSpeed) :
    flakes(numFlakes)
{
    for (int i = 0; i < numFlakes; ++i) {
        float x = static_cast<float>(RandomMaxMin(static_cast<int>(sf::VideoMode::getDesktopMode().width)));
        float y = static_cast<float>(RandomMaxMin(static_cast<int>(sf::VideoMode::getDesktopMode().height)));
        float speed = (minSpeed + static_cast<float>(rand()) / (RAND_MAX / (maxSpeed - minSpeed)));
        flakes[i] = Snowflake(sf::Vector2f(x, y), speed);
    }
}

void Snow::update(float dt) {
    for (Snowflake& flake : flakes) {
        flake.update(dt);
    }
}

void Snow::draw(sf::RenderTarget& target) {
    for (Snowflake& flake : flakes) {
        flake.draw(target);
    }
}
