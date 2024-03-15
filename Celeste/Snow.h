#include <SFML/Graphics.hpp>
#include <vector>
#include "Snowflake.h"


class Snow {
public:
    Snow() {};
    Snow(int _numFlakes, float _minSpeed, float _maxSpeed);

    void update(float _dt);
    void draw(sf::RenderTarget& _target);

private:
    std::vector<Snowflake> flakes;
};


