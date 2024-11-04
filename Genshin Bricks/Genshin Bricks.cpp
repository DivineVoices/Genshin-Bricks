#include "Fct_Gen.h"
#include "Decla_ball.h"
#include "Decla_block.h"
#include "Decla_Screen.h"

int main() 
{
    //A ne pas toucher
    Screen Window;
    sf::ContextSettings settings = Window.Demarrage();
    Vector2 windowSize = Window.GetSize(); 
    sf::RenderWindow window(sf::VideoMode(windowSize.m_x, windowSize.m_y), "Genshin Bricks", sf::Style::Default, settings);
    //A partir de là, c'est bon

    
    sf::Font font;
    /*
    // Load the font file; replace "path/to/font.ttf" with the actual path to your font file.
    if (!font.loadFromFile("zh-cn.ttf")) {
        std::cerr << "Error loading font\n";
        return -1;
    }
    */


    int ballSize(10);

    //Création de balles
    Ball balle(ballSize, (300, 400), Vector2(0.1f, 0.1f), 1);


    //Initialisation de Ball
    balle.CreaBall();

    sf::Color Anemo(116, 194, 168, 255);
    sf::Color Electro(167, 86, 204, 255);
    sf::Color Pyro(239, 121, 56, 255);
    sf::Color eleStorage[] = { Anemo, Electro, Pyro };

    //Pour les switch statement, Flying/Reposition = ballState, Running/GameWin/GameOver = gameState
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

    sf::Clock gameClock;
    sf::Time electroDur;
    Vector2 paddleSize(100, 30);
    Vector2 brickSize(80, 40);
    int eleSwitcher(0);
    int lives(3);
    bool ballVisible = true;
    sf::CircleShape Ball(10);
    sf::RectangleShape Paddle(sf::Vector2f(paddleSize.m_x, paddleSize.m_y));
    sf::RectangleShape Brick(sf::Vector2f(brickSize.m_x, brickSize.m_y));
    sf::Vector2i mousePosition = sf::Mouse::getPosition();
    Vector2 ballStartPos(300, 400);
    Vector2 speed(0.1f, 0.1f);
    sf::Time electroDuration;
    bool electroSpeed = false;
    bool brickVisible = true;
    bool electroSpeedEnhanced = false;
    bool winCon = false;
    Ball.setFillColor(Anemo);
    Paddle.setFillColor(Anemo);
    Brick.setFillColor(Electro);
    Ball.setPosition(ballStartPos.m_x, ballStartPos.m_y);
    Paddle.setPosition(0, 750);
    window.setKeyRepeatEnabled(false);
    sf::Text text;


    //Evenements a ne pas toucher
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
                    switch (gameState) {
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
                        break;

                    case GameWin:
                        std::cout << "GameWin left click registered" << std::endl;
                        break;
                    }
                }
                if (event.mouseButton.button == sf::Mouse::Right)
                {
                    ballState = Flying;
                }
            }
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.scancode == sf::Keyboard::Scan::R)
                {
                    switch (gameState) {
                    case Running:
                        std::cout << "Running R registered" << std::endl;
                        break;
                    case GameOver:
                        std::cout << "GameOver R registered" << std::endl;
                        Ball.setPosition(ballStartPos.m_x, ballStartPos.m_y); // Reset ball position
                        speed = Vector2(0.1f, 0.1f);
                        lives = 3;
                        ballVisible = true;
                        brickVisible = true;
                        electroSpeed = false;
                        electroSpeedEnhanced = false;
                        winCon = false;
                        gameState = Running;
                        ballState = Reposition;
                        break;

                    case GameWin:
                        std::cout << "GameWin R registered" << std::endl;
                        Ball.setPosition(ballStartPos.m_x, ballStartPos.m_y); // Reset ball position
                        speed = Vector2(0.1f, 0.1f);
                        lives = 3;
                        ballVisible = true;
                        brickVisible = true; // Make sure brick is visible again
                        electroSpeed = false;
                        electroSpeedEnhanced = false;
                        winCon = false;
                        gameState = Running;
                        ballState = Reposition;
                        Brick.setPosition(((windowSize.m_x / 2) - (brickSize.m_x / 2)), 200); // Reposition brick
                        break;
                    }
                }
            }
        }

        switch (gameState)
        {
        case Running:
            switch (ballState)
            {
            case Flying:
                Ball.move(speed.m_x, speed.m_y);

                if ((Ball.getPosition().x >= (windowSize.m_x - (ballSize * 2))) || (Ball.getPosition().x <= 0)) {
                    speed.m_x *= -1.0f; // Reverse x speed on wall collision
                }
                if ((Ball.getPosition().y >= (windowSize.m_y - (ballSize * 2))) || (Ball.getPosition().y <= 0)) {
                    speed.m_y *= -1.0f; // Reverse y speed on wall collision
                }

                break;
            case Reposition:
                Ball.setPosition(mousePosition.x - ballSize, 730);
                break;
            }

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

            if (mousePosition.x >= (windowSize.m_x - (paddleSize.m_x / 2))) mousePosition.x = (windowSize.m_x - (paddleSize.m_x / 2));
            if (mousePosition.x <= (paddleSize.m_x / 2)) mousePosition.x = (paddleSize.m_x / 2);

            Paddle.setPosition(mousePosition.x - (paddleSize.m_x / 2), 750);
            Brick.setPosition(((windowSize.m_x / 2) - (brickSize.m_x / 2)), 200);


            if (electroSpeed) {
                // Check how much time has passed since electroSpeed was activated
                electroDuration = gameClock.getElapsedTime();

                // Check if the duration has exceeded 3 seconds
                if (electroDuration.asSeconds() >= 3) {
                    if (electroSpeedEnhanced == 1) {
                        electroSpeed = false; // Reset the speed flag
                        speed.m_x /= 2.0f;      // Reset speed to normal
                        speed.m_y /= 2.0f;      // Reset speed to normal
                    }
                    else {
                        electroSpeed = false; // Reset the speed flag
                        speed.m_x /= 1.5f;      // Reset speed to normal
                        speed.m_y /= 1.5f;
                    }
                }
            }

            if (paddleBox.intersects(ballBox))
            {
                // Calculate the ball's position to ensure it bounces correctly
                if (Ball.getPosition().y + ballSize * 2 >= Paddle.getPosition().y) {
                    // Move the ball just above the paddle to avoid hovering
                    Ball.setPosition(Ball.getPosition().x, Paddle.getPosition().y - ballSize * 2);
                    speed.m_y *= -1.0f; // Reverse y-speed
                    sf::Color elementChange = Paddle.getFillColor();
                    Ball.setFillColor(elementChange);
                }
            }

            if (brickBox.intersects(ballBox) && brickVisible) {
                brickVisible = false;
                speed.m_y *= -1.0f;
                //if wincon est une commande temporaire pour faire fonctionner le code, pour l'instant j'ai pas une bonne place pour la wincon alors elle est la comme example
                if (winCon) 
                {
                    gameState = GameWin;
                }

                if (Brick.getFillColor() == Electro)
                {
                    if (electroSpeed == false) {
                        if (Ball.getFillColor() == Anemo)
                        {
                            electroSpeedEnhanced = true;
                            electroSpeed = true; // Activate electro speed
                            speed.m_x *= 2.0f;     // Double the speed
                            speed.m_y *= 2.0f;     // Double the speed
                            gameClock.restart();  // Restart the game clock to track this effect duration
                        }
                        else
                        {
                            electroSpeedEnhanced = false;
                            electroSpeed = true; // Activate electro speed
                            speed.m_x *= 1.5f;     // Double the speed
                            speed.m_y *= 1.5f;     // Double the speed
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
            text.setPosition(windowSize.m_x / 2 - 100, windowSize.m_y / 2 - 25);

            window.clear();
            window.draw(text);
            window.display();
            break;

        case GameWin:
            text.setFont(font);
            text.setString("Let the wind guide you!");
            text.setCharacterSize(20);
            text.setFillColor(Anemo);
            text.setPosition(windowSize.m_x / 2 - 100, windowSize.m_y / 2 - 25);

            window.clear();
            window.draw(text);
            window.display();
            break;
        }
    }
    return 0;
}
