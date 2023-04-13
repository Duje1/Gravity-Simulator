#include <SFML/Graphics.hpp>
#include <string>
#include <cmath>
#include <iostream>
#include <sstream>


template <typename T>
inline std::string tostring(const T& v)
{
    std::stringstream s;
    s << v;
    return s.str();
}

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
        gravitySourceCircle.setRadius(4);

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
        return strength;
    }
};

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

    void render(sf::RenderWindow& win)
    {
        particleCircle.setPosition(pos);
        win.draw(particleCircle);
    }

    void updatePhysics(GravitySource& s)
    {
        float distanceX = s.getPosition().x - pos.x;
        float distanceY = s.getPosition().y - pos.y;

        float distance = sqrt(distanceX * distanceX + distanceY * distanceY);

        float inverseDistance = 1.f / distance;

        float normalizedX = inverseDistance * distanceX;
        float normalizedY = inverseDistance * distanceY;

        float inverseSquareDropoff = inverseDistance * inverseDistance;

        float accelerationX = normalizedX * s.getStrength() * inverseSquareDropoff;
        float accelerationY = normalizedY * s.getStrength() * inverseSquareDropoff;

        velocity.x += accelerationX;
        velocity.y += accelerationY;

        pos.x += velocity.x;
        pos.y += velocity.y;

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

    void render(sf::RenderWindow& win, Particle& particle, float fps,sf::Vector2f velocity, sf::Vector2f position)
    {

        fpsText.setString(tostring(fps) + " / 60");
        win.draw(fpsText);
        velocityText.setString("Velocity X : "+ tostring(velocity.x)+ " Velocity Y: " + tostring(velocity.y));
        win.draw(velocityText);
        positionText.setString("Positon X: " + tostring(position.x)+ " Position Y: " +tostring(position.y));
        win.draw(positionText);
    }
};



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

        float currentTime = clock.restart().asSeconds();
        float fps = 1.f / (currentTime);
        lastTime = currentTime;


        window.clear();

        particle.updatePhysics(source);
        source.render(window);
        infoText.render(window, particle, fps, particle.getVelocity(), particle.getPosition());
        particle.render(window);
        window.display();
    }

    return 0;

}
