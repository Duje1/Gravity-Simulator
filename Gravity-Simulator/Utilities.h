#pragma once

#include <sstream>

// Template function to convert any value to a string
template <typename T>
inline std::string tostring(const T& v)
{
    std::stringstream s;
    s << v;
    return s.str();
}

// Class for managing and rendering text information on the screen
class text_info
{
    std::string font_address;       // File path of the font
    sf::Font font;                  // Font object for text rendering
    sf::Text fpsText;               // For displaying frames per second (FPS)
    sf::Text velocityText;          // For displaying particle velocity
    sf::Text positionText;          // For displaying particle position
    sf::Text deltaTimeText;         // For displaying time between frames (delta time)
    sf::Text sourceStrengthText;    // For displaying gravitational source strength
    sf::Text numberOfParticlesText; // For displaying number of particles

public:
    // Initialize the font using a given address
    void initFont(sf::Font& font, std::string address)
    {
        this->font_address = address;
        if (!font.loadFromFile(address))
        {
            std::cout << "Failed to initialize font : " << address << std::endl;
        }
    }

    // Initialize text objects with font and positions
    void initText(std::string font_address)
    {
        initFont(font, font_address);

        // Configure FPS text
        fpsText.setFont(font);
        fpsText.setCharacterSize(15);
        fpsText.setPosition(100, 100);
        fpsText.setFillColor(sf::Color::White);

        // Configure delta time text
        deltaTimeText.setFont(font);
        deltaTimeText.setCharacterSize(15);
        deltaTimeText.setPosition(100, 115);
        deltaTimeText.setFillColor(sf::Color::Green);

        // Configure source strength text
        sourceStrengthText.setFont(font);
        sourceStrengthText.setCharacterSize(15);
        sourceStrengthText.setPosition(100, 130);
        sourceStrengthText.setFillColor(sf::Color(128, 128, 128));

        // Configure number of particles text
        numberOfParticlesText.setFont(font);
        numberOfParticlesText.setCharacterSize(15);
        numberOfParticlesText.setPosition(100, 145);
        numberOfParticlesText.setFillColor(sf::Color::White);

        // Configure velocity and position texts
        velocityText.setCharacterSize(15);
        velocityText.setFont(font);
        velocityText.setFillColor(sf::Color::Red);
        velocityText.setPosition(100, 160);

        positionText.setCharacterSize(15);
        positionText.setFont(font);
        positionText.setFillColor(sf::Color::Red);
        positionText.setPosition(100, 175);
    }

    // Render various text information on the provided SFML window
    void render(sf::RenderWindow& win, Particle& particle, GravitySource& source,
        float fps, float deltaTime, int numberOfParticles,
        sf::Vector2f velocity, sf::Vector2f position)
    {
        // Update and draw FPS text
        fpsText.setString(tostring(fps) + " / 60");
        win.draw(fpsText);

        // Update and draw delta time text
        deltaTimeText.setString("Delta Time: " + tostring(deltaTime) + " seconds");
        win.draw(deltaTimeText);

        // Update and draw source strength text
        sourceStrengthText.setString("Source Strength: " + tostring(source.getStrength()));
        win.draw(sourceStrengthText);

        // Update and draw number of particles text
        numberOfParticlesText.setString("Number of particles: " + tostring(numberOfParticles));
        win.draw(numberOfParticlesText);

        // Update and draw velocity text
        velocityText.setString("Velocity X: " + tostring(velocity.x) +
            " Velocity Y: " + tostring(velocity.y));
        win.draw(velocityText);

        // Update and draw position text
        positionText.setString("Position X: " + tostring(position.x) +
            " Position Y: " + tostring(position.y));
        win.draw(positionText);
    }
};