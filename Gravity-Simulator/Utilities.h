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

        velocityText.setCharacterSize(14);
        velocityText.setFont(font);
        velocityText.setFillColor(sf::Color::White);
        velocityText.setPosition(100, 115);

        positionText.setCharacterSize(14);
        positionText.setFont(font);
        positionText.setFillColor(sf::Color::White);
        positionText.setPosition(100, 130);
    }

    void render(sf::RenderWindow& win, Particle& particle, float fps, sf::Vector2f velocity, sf::Vector2f position)
    {
        fpsText.setString(tostring(fps) + " / 60");
        win.draw(fpsText);
        velocityText.setString("Velocity X : " + tostring(velocity.x) + " Velocity Y: " + tostring(velocity.y));
        win.draw(velocityText);
        positionText.setString("Positon X: " + tostring(position.x) + " Position Y: " + tostring(position.y));
        win.draw(positionText);
    }
};
