#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "GravitySource.h"
#include "Particle.h"
#include "Utilities.h"

int main()
{
    unsigned int FPS_LIMIT = 60;
    std::string VERSION = "1.0";

    sf::RenderWindow window(sf::VideoMode(1400, 768), "Gravity simulation " + VERSION);
    window.setFramerateLimit(FPS_LIMIT);
    
    GravitySource mainSource(680, 334, 5000);
    Particle mainParticle(400, 500, 400, 0, sf::Color::Red);
    Particle mouseParticle(- 10, - 10, 0, 0, sf::Color::Blue);

    std::vector<Particle> particles;
    text_info infoText;
    infoText.initText("D:\\fonts\\OpenSans\\OpenSans-Light.ttf");

    sf::Clock clock;
    sf::Clock deltaClock;

    float lastTime = 0;
    sf::Vector2i localMousePosition;
    while (window.isOpen())
    {

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == event.Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) window.close();
        }

        // Get the fps
        float currentTime = clock.restart().asSeconds();
        float fps = 1.f / (currentTime);
        lastTime = currentTime;

        // Get delta time
        float deltaTime = deltaClock.restart().asSeconds();

        // Get the local mouse position (relative to a window)
        localMousePosition = sf::Mouse::getPosition(window);
        mouseParticle.setPosition(sf::Vector2f(localMousePosition.x - 7, localMousePosition.y -10));

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            particles.push_back(Particle(localMousePosition.x,localMousePosition.y,400,0,sf::Color::White));
        }

        // Rendering
        window.clear();
        for (int i = 0; i < particles.size(); i++)
        {
            particles[i].updatePhysics(mainSource, deltaTime);
            particles[i].render(window);
        }
        mainParticle.updatePhysics(mainSource, deltaTime);
        mainSource.render(window);
        infoText.render(window, mainParticle, mainSource, fps, deltaTime, particles.size()+1, mainParticle.getVelocity(), mainParticle.getPosition());
        mainParticle.render(window);
        mouseParticle.render(window);
        window.display();
    }

    return 0;

}
