#include <SFML/Graphics.hpp>
#include "TextureManager.h"

class Snowflake {
public:
    Snowflake(sf::Vector2f _position, float _speed);
    Snowflake();


    void update(float dt);
    void draw(sf::RenderTarget& _target);

private:
    sf::CircleShape* shape;
    sf::Vector2f position;
    float speed;
};

