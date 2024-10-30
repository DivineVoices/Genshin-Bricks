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
    sf::Font font;
    // Load the font file; replace "path/to/font.ttf" with the actual path to your font file.
    if (!font.loadFromFile("zh-cn.ttf")) {
        std::cerr << "Error loading font\n";
        return -1;
    }
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
    int lives(3);
    bool ballVisible = true;
    sf::CircleShape Ball(ballSize);
    sf::RectangleShape Paddle(sf::Vector2f(paddleSize.x, paddleSize.y));
    sf::RectangleShape Brick(sf::Vector2f(brickSize.x, brickSize.y));
    sf::Vector2i mousePosition = sf::Mouse::getPosition();
    Vector2 ballStartPos(300, 400);
    Vector2 speed(0.1f, 0.1f);
    sf::Time electroDuration;
    bool electroSpeed = false;
    bool brickVisible = true;
    bool electroSpeedEnhanced = false;
    Ball.setFillColor(Anemo);
    Paddle.setFillColor(Anemo);
    Brick.setFillColor(Electro);
    Ball.setPosition(ballStartPos.x, ballStartPos.y);
    Paddle.setPosition(0, 750);
    window.setKeyRepeatEnabled(false);
    sf::Text text;


    enum State
    {
        Flying,
        Reposition,
        Running,
        GameOver,
        GameWin,
    };

    State gameState = Running;

    State ballState = Flying;

    while (window.isOpen())
    {
        sf::FloatRect paddleBox = Paddle.getGlobalBounds();
        sf::FloatRect ballBox = Ball.getGlobalBounds();
        sf::FloatRect brickBox = Brick.getGlobalBounds();
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    std::cout << "Left click registered" << std::endl;
                    switch(gameState) {
                    case Running: 
                        std::cout << "Running left click registered" << std::endl;
                        eleSwitcher += 1;
                        if (eleSwitcher > 2) {
                            eleSwitcher = 0;
                        }
                        Paddle.setFillColor(eleStorage[eleSwitcher]);
                        break;

                    case GameOver:
                        std::cout << "GameOver left click registered" << std::endl;
                        lives = 3;
                        ballVisible = true;
                        brickVisible = true;
                        electroSpeed = false;
                        electroSpeedEnhanced = false;
                        gameState = Running;
                        break;

                    case GameWin:
                        std::cout << "GameWin left click registered" << std::endl;
                        lives = 3;
                        ballVisible = true;
                        brickVisible = true;
                        electroSpeed = false;
                        electroSpeedEnhanced = false;
                        gameState = Running;
                        break;
                    }
                }
            }
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Right)
                {
                    ballState = Flying;
                }
            }
        }
        switch (gameState)
        {
        case Running:
            switch (ballState)
            {
            case Flying:
                Ball.move(speed.x, speed.y);

                if ((Ball.getPosition().x >= (screenSize.x - (ballSize * 2))) || (Ball.getPosition().x <= 0)) {
                    speed.x *= -1.0f; // Reverse x speed on wall collision
                }
                if ((Ball.getPosition().y >= (screenSize.y - (ballSize * 2))) || (Ball.getPosition().y <= 0)) {
                    speed.y *= -1.0f; // Reverse y speed on wall collision
                }

                break;
            case Reposition:
                Ball.setPosition(mousePosition.x - ballSize, 730);
                break;
            }


            // Update game logic
            window.clear();
            window.draw(Ball);
            window.draw(Paddle);
            if (brickVisible) {
                window.draw(Brick);
            }
            window.display();

            if (lives <= 0)
            {
                gameState = GameOver;
            }

            if (Ball.getPosition().y >= 770) {
                lives -= 1;
                std::cout << lives << std::endl;
                ballState = Reposition;
            }
            mousePosition = sf::Mouse::getPosition(window);

            if (mousePosition.x >= (screenSize.x - (paddleSize.x / 2))) mousePosition.x = (screenSize.x - (paddleSize.x / 2));
            if (mousePosition.x <= (paddleSize.x / 2)) mousePosition.x = (paddleSize.x / 2);

            Paddle.setPosition(mousePosition.x - (paddleSize.x / 2), 750);
            Brick.setPosition(((screenSize.x / 2) - (brickSize.x / 2)), 200);


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
                // Calculate the ball's position to ensure it bounces correctly
                if (Ball.getPosition().y + ballSize * 2 >= Paddle.getPosition().y) {
                    // Move the ball just above the paddle to avoid hovering
                    Ball.setPosition(Ball.getPosition().x, Paddle.getPosition().y - ballSize * 2);
                    speed.y *= -1.0f; // Reverse y-speed
                    sf::Color elementChange = Paddle.getFillColor();
                    Ball.setFillColor(elementChange);
                }
            }

            if (brickBox.intersects(ballBox) && brickVisible) {
                brickVisible = false;
                speed.y *= -1.0f;
                gameState = GameWin;
                if (Brick.getFillColor() == Electro)
                {
                    if (electroSpeed == false) {
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
            break;
        case GameOver:
            text.setFont(font);
            text.setString("The abyss claims all.");
            text.setCharacterSize(20);
            text.setFillColor(Electro);
            text.setPosition(screenSize.x / 2 - 100, screenSize.y / 2 - 25);

            window.clear();
            window.draw(text);
            window.display();
            break;

        case GameWin:
            text.setFont(font);
            text.setString("Let the wind guide you!");
            text.setCharacterSize(20);
            text.setFillColor(Anemo);
            text.setPosition(screenSize.x / 2 - 100, screenSize.y / 2 - 25);

            window.clear();
            window.draw(text);
            window.display();
            break;

        }
    }
}