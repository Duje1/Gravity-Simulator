#include <iostream>
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
    
    GravitySource source(680, 334, 10000);
    Particle particle(400, 500, 4, 0);
    text_info infoText;
    infoText.initText("D:\\fonts\\OpenSans\\OpenSans-Light.ttf");


    sf::Clock clock;
    float lastTime = 0;

    while (window.isOpen())
    {

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == event.Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) window.close();
        }

        //Get the fps
        float currentTime = clock.restart().asSeconds();
        float fps = 1.f / (currentTime);
        lastTime = currentTime;

        //Rendering
        window.clear();
        particle.updatePhysics(source);
        source.render(window);
        infoText.render(window, particle, fps, particle.getVelocity(), particle.getPosition());
        particle.render(window);
        window.display();
    }

    return 0;

}