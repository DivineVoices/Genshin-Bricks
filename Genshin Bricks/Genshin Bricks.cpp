#include "Decla_Game.h"

int main() 
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> alea(0.3, 0.7);

    //A ne pas toucher
    Screen screen;
    Ball balle;
    Paddle paddle;
    Game game(screen,balle,paddle);

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    Vector2 windowSize = game.GetScreenSize();
    sf::RenderWindow window(sf::VideoMode(windowSize.m_x, windowSize.m_y), "Genshin Bricks", sf::Style::Default, settings);
    sf::Font font;
    if (!font.loadFromFile("zh-cn.ttf")) {
        std::cerr << "Error loading font\n";
    }
    
    //Init couleurs
    sf::Color colorAnemo(116, 194, 168, 255);
    sf::Color colorElectro(167, 86, 204, 255);
    sf::Color colorPyro(239, 121, 56, 255);
    sf::Color colorWhite(255, 255, 255, 255);
    sf::Color eleStorage[] = { colorAnemo, colorElectro, colorPyro };

    //Init Clock
    sf::Clock gameClock;
    sf::Time electroDur;

    Vector2 brickSize(80, 40);
    sf::RectangleShape Brick(sf::Vector2f(brickSize.m_x, brickSize.m_y));

    sf::Vector2i mousePosition = sf::Mouse::getPosition();
    Vector2 speed(0.1f, 0.1f);
    sf::Time electroDuration;
    bool electroSpeed = false;
    bool brickVisible = true;
    bool electroSpeedEnhanced = false;
    bool winCon = false;
    Brick.setFillColor(colorElectro);
    window.setKeyRepeatEnabled(false);

    //Démarrage
    game.SetGameState(Running);

    //Evenements a ne pas toucher
    while (window.isOpen())
    {
        Ball vrballe = game.GetBall();
        Paddle vrpaddle = game.GetPaddle();

        sf::CircleShape forballebox = vrballe.GetForm();
        sf::RectangleShape forpaddlebox = vrpaddle.GetForm();

        sf::FloatRect paddleBox = forpaddlebox.getGlobalBounds();
        sf::FloatRect ballBox = forballebox.getGlobalBounds();
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
                    game.LeftClick();
                }
                if (event.mouseButton.button == sf::Mouse::Right)
                {
                    balle.SetBallState(Flying);
                }
            }
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.scancode == sf::Keyboard::Scan::R)
                {
                    switch (game.GetGameState()) {
                    case Running:
                        std::cout << "Running R registered" << std::endl;
                        break;
                    case GameOver:
                        std::cout << "GameOver R registered" << std::endl;
                        game.RestartGame();
                        brickVisible = true;
                        electroSpeed = false;
                        electroSpeedEnhanced = false;
                        winCon = false;
                        break;

                    case GameWin:
                        std::cout << "GameWin R registered" << std::endl;
                        game.RestartGame();
                        electroSpeed = false;
                        electroSpeedEnhanced = false;
                        winCon = false;
                        Brick.setPosition(((windowSize.m_x / 2) - (brickSize.m_x / 2)), 200); // Reposition brick
                        break;
                    }
                }
            }
        }

        switch (game.GetGameState())
        {
        case Running:
            switch (game.GetBallState())
            {
            case Flying:

                balle.MoveBall(screen);

                break;
            case Repositionning:
                
                vrballe.SetPos(Vector2 (mousePosition.x - vrballe.GetSize(), 730));
                break;
            }

            window.clear();
            window.draw(vrballe.GetForm());
            window.draw(vrpaddle.GetForm());
            if (brickVisible) {
                window.draw(Brick);
            }
            window.display();


            if (paddle.GetLife() <= 0)
            {
                game.SetGameState(GameOver);
            }

            if (vrballe.GetPos().m_y >= 770) {
                game.Death();
            }
            mousePosition = sf::Mouse::getPosition(window);

            if (mousePosition.x >= (windowSize.m_x - (vrpaddle.GetSize().m_x / 2))) mousePosition.x = (windowSize.m_x - (vrpaddle.GetSize().m_x / 2));
            if (mousePosition.x <= (vrpaddle.GetSize().m_x / 2)) mousePosition.x = (vrpaddle.GetSize().m_x / 2);

            vrpaddle.SetPos(Vector2(mousePosition.x - (vrpaddle.GetSize().m_x / 2), 750));
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
                if (vrballe.GetPos().m_y + balle.GetSize() * 2 >= vrpaddle.GetPos().m_y) {
                    // Move the ball just above the paddle to avoid hovering
                    vrballe.SetPos(Vector2 (vrballe.GetPos().m_x, vrpaddle.GetPos().m_y - balle.GetSize() * 2));
                    speed.m_y *= -1.0f; // Reverse y-speed
                }
            }

            if (brickBox.intersects(ballBox) && brickVisible) {
                brickVisible = false;
                speed.m_y *= -1.0f;
                //if wincon est une commande temporaire pour faire fonctionner le code, pour l'instant j'ai pas une bonne place pour la wincon alors elle est la comme example
                if (winCon) 
                {
                    game.SetGameState(GameWin);
                }

                if (Brick.getFillColor() == colorElectro)
                {
                    if (electroSpeed == false) {
                        if (vrballe.GetEle() == Anemo)
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
            window.clear();
            window.draw(game.TextGameOver(colorElectro,windowSize,font));
            window.display();
            break;

        case GameWin:
            window.clear();
            window.draw(game.TextGameOver(colorAnemo, windowSize,font));
            window.display();
            break;
        }
    }
    return 0;
}