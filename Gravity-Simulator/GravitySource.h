#pragma once

#include <SFML/Graphics.hpp>

// Class representing a gravitational source in the simulation
class GravitySource
{
    sf::Vector2f pos;                    // Position of the gravitational source
    float strength;                      // Strength of the gravitational source
    sf::CircleShape gravitySourceCircle; // Graphical representation of the source

public:
    // Initialize gravitational source attributes
    GravitySource(float pos_x, float pos_y, float strength)
    {
        // Set initial position, strength, and configure graphical representation
        pos.x = pos_x;
        pos.y = pos_y;
        this->strength = strength;
        gravitySourceCircle.setPosition(pos);
        gravitySourceCircle.setFillColor(sf::Color::White);
        gravitySourceCircle.setRadius(8);
    }

    // Render the gravitational source on the SFML window
    void render(sf::RenderWindow& win)
    {
        win.draw(gravitySourceCircle);
    }

    // Get the gravitational source's position
    sf::Vector2f getPosition()
    {
        return pos;
    }

    // Get the scaled gravitational strength
    float getStrength()
    {
        // Scale the strength for better visualization (e.g., on graphical representations)
        return strength * 10000;
    }
};