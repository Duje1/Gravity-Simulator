#pragma once
#include <SFML/Graphics.hpp>
#include "GravitySource.h"

class Particle
{


    sf::Vector2f pos;
    sf::Vector2f velocity;
    sf::CircleShape particleCircle;

public:


    Particle(float pos_x, float pos_y, float velocity_x, float velocity_y)
    {

        pos.x = pos_x;
        pos.y = pos_y;

        velocity.x = velocity_x;
        velocity.y = velocity_y;

        particleCircle.setPosition(pos);
        particleCircle.setFillColor(sf::Color::White);
        particleCircle.setRadius(4);

    }


    void setPosition(sf::Vector2f pos)
    {
        this->pos = pos;

    }

    void render(sf::RenderWindow& win)
    {
        particleCircle.setPosition(pos);
        win.draw(particleCircle);
    }

    void updatePhysics(GravitySource& s, float deltaTime)
    {
        float distanceX = s.getPosition().x - pos.x;
        float distanceY = s.getPosition().y - pos.y;

        float distance = sqrt(distanceX * distanceX + distanceY * distanceY);

        float inverseDistance = 1.f / distance;

        float normalizedX = inverseDistance * distanceX;
        float normalizedY = inverseDistance * distanceY;

        float inverseSquareDropoff = inverseDistance * inverseDistance;

        float accelerationX = normalizedX * s.getStrength() * inverseSquareDropoff ;
        float accelerationY = normalizedY * s.getStrength() * inverseSquareDropoff ;

        
        velocity.x += accelerationX * deltaTime;
        velocity.y += accelerationY * deltaTime;

        pos.x += velocity.x * deltaTime;
        pos.y += velocity.y * deltaTime;

    }

    sf::Vector2f getPosition()
    {
        return pos;
    }

    sf::Vector2f getVelocity()
    {
        return velocity;
    }


};

