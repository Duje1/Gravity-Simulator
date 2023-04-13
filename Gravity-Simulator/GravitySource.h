#pragma once
#include <SFML/Graphics.hpp>
class GravitySource
{
    sf::Vector2f pos;
    float strength;
    sf::CircleShape gravitySourceCircle;


public:

    GravitySource(float pos_x, float pos_y, float strength)
    {

        pos.x = pos_x;
        pos.y = pos_y;
        this->strength = strength;

        gravitySourceCircle.setPosition(pos);
        gravitySourceCircle.setFillColor(sf::Color::White);
        gravitySourceCircle.setRadius(8);

    }

    void render(sf::RenderWindow& win)
    {
        win.draw(gravitySourceCircle);
    }

    sf::Vector2f getPosition()
    {
        return pos;
    }

    float getStrength()
    {
        return strength * 10000;
    }
};