#pragma once
#include <sstream>
template <typename T>
inline std::string tostring(const T& v)
{
    std::stringstream s;
    s << v;
    return s.str();
}

class text_info
{
    std::string font_address;
    sf::Font font;
    sf::Text fpsText;
    sf::Text velocityText;
    sf::Text positionText;
    sf::Text deltaTimeText;
    sf::Text sourceStrengthText;
    sf::Text numberOfParticlesText;
public:

    void initFont(sf::Font& font, std::string address)
    {
        this->font_address = address;
        if (!font.loadFromFile(address))
        {
            std::cout << "Failed to initialize font : " << address << std::endl;
        }
    }

    void initText(std::string font_address)
    {
        initFont(font, font_address);

        fpsText.setFont(font);
        fpsText.setCharacterSize(15);
        fpsText.setPosition(100, 100);
        fpsText.setFillColor(sf::Color::White);

        deltaTimeText.setFont(font);
        deltaTimeText.setCharacterSize(15);
        deltaTimeText.setPosition(100, 115);
        deltaTimeText.setFillColor(sf::Color::Green);

        sourceStrengthText.setFont(font);
        sourceStrengthText.setCharacterSize(15);
        sourceStrengthText.setPosition(100, 130);
        sourceStrengthText.setFillColor(sf::Color(128, 128, 128));

        numberOfParticlesText.setFont(font);
        numberOfParticlesText.setCharacterSize(15);
        numberOfParticlesText.setPosition(100, 145);
        numberOfParticlesText.setFillColor(sf::Color::White);

        velocityText.setCharacterSize(15);
        velocityText.setFont(font);
        velocityText.setFillColor(sf::Color::Red);
        velocityText.setPosition(100, 160);

        positionText.setCharacterSize(15);
        positionText.setFont(font);
        positionText.setFillColor(sf::Color::Red);
        positionText.setPosition(100, 175);
    }

    void render(sf::RenderWindow& win, Particle& particle, GravitySource& source,float fps, float deltaTime, int numberOfParticles, sf::Vector2f velocity, sf::Vector2f position)
    {
        fpsText.setString(tostring(fps) + " / 60");
        win.draw(fpsText);
        deltaTimeText.setString("Delta Time: " + tostring( deltaTime) + " seconds");
        win.draw(deltaTimeText);
        sourceStrengthText.setString("Source Strenght: " + tostring(source.getStrength()));
        win.draw(sourceStrengthText);
        numberOfParticlesText.setString("Number of particles: " + tostring(numberOfParticles));
        win.draw(numberOfParticlesText);
        velocityText.setString("Velocity X : " + tostring(velocity.x) + " Velocity Y: " + tostring(velocity.y));
        win.draw(velocityText);
        positionText.setString("Positon X: " + tostring(position.x) + " Position Y: " + tostring(position.y));
        win.draw(positionText);
    }
};
