#include "Fct_Gen.h"
#include "Decla_ball.h"
#include "Decla_block.h"

int main()
{

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    Vector2 screenSize(600, 800);
    sf::RenderWindow window(sf::VideoMode(screenSize.m_x, screenSize.m_y), "Genshin Bricks", sf::Style::Default, settings);

    sf::Color Anemo(116, 194, 168, 255);
    sf::Color Geo(253, 178, 12, 255);
    sf::Color Pyro(239, 121, 56, 255);
    float ballSize(10);
    sf::CircleShape shape(ballSize);
    Vector2 ballPos(300, 400);
    Vector2 speed(0.1f, 0.1f);

    shape.setFillColor(Anemo);
    shape.setPosition(ballPos.m_x, ballPos.m_y);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
        
        
        ballPos.m_x += speed.m_x;
        ballPos.m_y += speed.m_y;
        if ((ballPos.m_x >= (screenSize.m_x - (ballSize*2))) || (ballPos.m_x <= 0)) speed.m_x *= -1.0f;
        if ((ballPos.m_y >= (screenSize.m_y - (ballSize*2))) || (ballPos.m_y <= 0)) speed.m_y *= -1.0f;
        shape.move(speed.m_x, speed.m_y);

        
    }

    return 0;
}
