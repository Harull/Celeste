#include <SFML/Graphics.hpp>
#include <vector>
#include "Snowflake.h"

class Snow {
public:
    Snow() {};
    Snow(int numFlakes, float minSpeed, float maxSpeed);

    void update(float dt);
    void draw(sf::RenderTarget& target);

private:
    std::vector<Snowflake> flakes;
};


