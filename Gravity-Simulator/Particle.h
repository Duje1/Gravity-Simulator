#pragma once

#include <SFML/Graphics.hpp>
#include "GravitySource.h"

// Class representing a particle in the simulation
class Particle
{
    sf::Vector2f pos;               // Position of the particle
    sf::Vector2f velocity;          // Velocity of the particle
    sf::CircleShape particleCircle; // Graphical representation of the particle
    sf::Color color;                // Color of the particle

public:
    // Initialize particle attributes
    Particle(float pos_x, float pos_y, float velocity_x, float velocity_y, sf::Color color)
    {
        this->color = color;

        // Set initial position and velocity
        pos.x = pos_x;
        pos.y = pos_y;
        velocity.x = velocity_x;
        velocity.y = velocity_y;

        // Set up graphical representation
        particleCircle.setPosition(pos);
        particleCircle.setFillColor(color);
        particleCircle.setRadius(4);
    }

    // Update the particle's color
    void setColor(sf::Color color)
    {
        this->color = color;
        particleCircle.setFillColor(color);
    }

    // Set the position of the particle
    void setPosition(sf::Vector2f pos)
    {
        this->pos = pos;
    }

    // Render the particle on the SFML window provided
    void render(sf::RenderWindow& win)
    {
        particleCircle.setPosition(pos);
        win.draw(particleCircle);
    }

    // Update particle physics based on gravitational forces
    void updatePhysics(GravitySource& s, float deltaTime)
    {
        // Calculate the distance components between the particle and the gravity source
        float distanceX = s.getPosition().x - pos.x;
        float distanceY = s.getPosition().y - pos.y;

        // Calculate the Euclidean distance between the particle and the gravity source
        float distance = sqrt(distanceX * distanceX + distanceY * distanceY);

        // Calculate the inverse of the distance for normalization
        float inverseDistance = 1.f / distance;

        // Normalize the distance components to get normalized directions
        float normalizedX = inverseDistance * distanceX;
        float normalizedY = inverseDistance * distanceY;

        // Calculate the inverse square drop-off factor
        float inverseSquareDropoff = inverseDistance * inverseDistance;

        // Calculate acceleration components based on normalized directions, source strength, and inverse square drop-off
        float accelerationX = normalizedX * s.getStrength() * inverseSquareDropoff;
        float accelerationY = normalizedY * s.getStrength() * inverseSquareDropoff;

        // Update particle's velocity based on calculated acceleration and delta time
        velocity.x += accelerationX * deltaTime;
        velocity.y += accelerationY * deltaTime;

        // Update particle's position based on updated velocity and delta time
        pos.x += velocity.x * deltaTime;
        pos.y += velocity.y * deltaTime;
    }

    // Get the particle's position
    sf::Vector2f getPosition()
    {
        return pos;
    }

    // Get the particle's velocity
    sf::Vector2f getVelocity()
    {
        return velocity;
    }
};