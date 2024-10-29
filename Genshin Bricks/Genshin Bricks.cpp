#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Window/Mouse.hpp>



int main()
{
    struct Vector2 {
        float x, y;
        Vector2(float _x = 0, float _y = 0) : x(_x), y(_y) {}
    };
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    Vector2 screenSize(600, 800);
    sf::RenderWindow window(sf::VideoMode(screenSize.x, screenSize.y), "Genshin Bricks", sf::Style::Default, settings);
    sf::Color Anemo(116, 194, 168, 255);
    sf::Color Electro(167, 86, 204, 255);
    sf::Color Pyro(239, 121, 56, 255);
    sf::Color eleStorage[] = { Anemo, Electro, Pyro };
    float ballSize(10);
    sf::Clock gameClock;
    sf::Time electroDur;
    Vector2 paddleSize(100, 30);
    Vector2 brickSize(80, 40);
    int eleSwitcher(0);
    sf::CircleShape Ball(ballSize);
    sf::RectangleShape Paddle(sf::Vector2f(paddleSize.x, paddleSize.y));
    sf::RectangleShape Brick(sf::Vector2f(brickSize.x, brickSize.y));
    sf::Vector2i mousePosition = sf::Mouse::getPosition();
    Vector2 ballPos(300, 400);
    Vector2 speed(0.1f, 0.1f);
    sf::Time electroDuration;
    bool electroSpeed = false;
    bool brickVisible = true;
    bool electroSpeedEnhanced = false;
    Ball.setFillColor(Anemo);
    Paddle.setFillColor(Anemo);
    Brick.setFillColor(Electro);
    Ball.setPosition(ballPos.x, ballPos.y);
    Paddle.setPosition(0, 750);
    window.setKeyRepeatEnabled(false);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    eleSwitcher += 1;
                    if (eleSwitcher > 2) {
                        eleSwitcher = 0;
                    }
                    Paddle.setFillColor(eleStorage[eleSwitcher]);
                }
            }
        }

        // Update game logic
        window.clear();
        window.draw(Ball);
        window.draw(Paddle);
        if (brickVisible) {
            window.draw(Brick);
        }
        window.display();

        ballPos.x += speed.x;
        ballPos.y += speed.y;

        if ((ballPos.x >= (screenSize.x - (ballSize * 2))) || (ballPos.x <= 0)) speed.x *= -1.0f;
        if ((ballPos.y >= (screenSize.y - (ballSize * 2))) || (ballPos.y <= 0)) speed.y *= -1.0f;

        Ball.move(speed.x, speed.y);
        mousePosition = sf::Mouse::getPosition(window);

        if (mousePosition.x >= (screenSize.x - (paddleSize.x / 2))) mousePosition.x = (screenSize.x - (paddleSize.x / 2));
        if (mousePosition.x <= (paddleSize.x / 2)) mousePosition.x = (paddleSize.x / 2);

        Paddle.setPosition(mousePosition.x - (paddleSize.x / 2), 750);
        Brick.setPosition(((screenSize.x / 2) - (brickSize.x / 2)), 200);
        sf::FloatRect paddleBox = Paddle.getGlobalBounds();
        sf::FloatRect ballBox = Ball.getGlobalBounds();
        sf::FloatRect brickBox = Brick.getGlobalBounds();

        if (electroSpeed) {
            // Check how much time has passed since electroSpeed was activated
            electroDuration = gameClock.getElapsedTime();

            // Check if the duration has exceeded 3 seconds
            if (electroDuration.asSeconds() >= 3) {
                if (electroSpeedEnhanced == 1) {
                    electroSpeed = false; // Reset the speed flag
                    speed.x /= 2.0f;      // Reset speed to normal
                    speed.y /= 2.0f;      // Reset speed to normal
                }
                else {
                    electroSpeed = false; // Reset the speed flag
                    speed.x /= 1.5f;      // Reset speed to normal
                    speed.y /= 1.5f;
                }
            }
        }

        if (paddleBox.intersects(ballBox))
        {
            speed.y *= -1.0f;
            sf::Color elementChange = Paddle.getFillColor();
            Ball.setFillColor(elementChange);
        }

        if (brickBox.intersects(ballBox) && brickVisible) {
            brickVisible = false;
            speed.y *= -1.0f;
            if (Brick.getFillColor() == Electro)
            { 
                if (Ball.getFillColor() == Anemo) 
                    {
                        electroSpeedEnhanced = true;
                        electroSpeed = true; // Activate electro speed
                        speed.x *= 2.0f;     // Double the speed
                        speed.y *= 2.0f;     // Double the speed
                        gameClock.restart();  // Restart the game clock to track this effect duration
                    }
                else 
                {
                    electroSpeedEnhanced = false;
                    electroSpeed = true; // Activate electro speed
                    speed.x *= 1.5f;     // Double the speed
                    speed.y *= 1.5f;     // Double the speed
                    gameClock.restart();
                }
            }
        }


    }
}