#include <SFML/Graphics.hpp>

class Snowflake {
public:
    Snowflake(sf::Vector2f position, float speed);
    Snowflake();


    void update(float dt);
    void draw(sf::RenderTarget& target);

private:
    sf::CircleShape shape;
    sf::Vector2f position;
    float speed;
};

