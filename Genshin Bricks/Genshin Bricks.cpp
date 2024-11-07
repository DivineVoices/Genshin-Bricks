#include <iostream>
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Audio.hpp>

using namespace std;

struct Vector2 {
    float x, y;
    Vector2(float _x = 0, float _y = 0) : x(_x), y(_y) {}
};

class Brick
{
public:
    Vector2 position;
    sf::Color Element;
    bool is_visible;
    sf::FloatRect brickBox;
    sf::Sprite sprite;

    static sf::Texture anemoTexture;
    static sf::Texture electroTexture;
    static sf::Texture pyroTexture;

    Brick() : is_visible(true) {}

    static void loadTextures() {
        if (!anemoTexture.loadFromFile("anemo.png")) {
            cerr << "Erreur de chargement de la texture anemo.png" << endl;
        }
        if (!electroTexture.loadFromFile("electro.png")) {
            cerr << "Erreur de chargement de la texture electro.png" << endl;
        }
        if (!pyroTexture.loadFromFile("pyro.png")) {
            cerr << "Erreur de chargement de la texture pyro.png" << endl;
        }
    }

    void init(sf::Color element, Vector2 position, Vector2 size) {
        this->position = position;
        this->Element = element;
        is_visible = true;

        // Appliquer la bonne texture selon l'élément
        if (Element == sf::Color(239, 121, 56, 255)) {  // Pyro
            sprite.setTexture(pyroTexture);
        }
        else if (Element == sf::Color(116, 194, 168, 255)) {  // Anemo
            sprite.setTexture(anemoTexture);
        }
        else if (Element == sf::Color(167, 86, 204, 255)) {  // Electro
            sprite.setTexture(electroTexture);
        }

        sprite.setPosition(position.x, position.y);
        sprite.setScale(size.x / sprite.getTexture()->getSize().x, size.y / sprite.getTexture()->getSize().y);
        brickBox = sprite.getGlobalBounds();
    }
};

// Initialisation des textures statiques
sf::Texture Brick::anemoTexture;
sf::Texture Brick::electroTexture;
sf::Texture Brick::pyroTexture;

bool checkWinCondition(const vector<Brick>& bricks) {
    for (const auto& brick : bricks) {
        if (brick.is_visible) {
            return false; // At least one brick is still visible, so the game is not won
        }
    }
    return true; // All bricks are invisible, the player has won
}
int getBrickIndex(int row, int col, int rows, int cols) {
    if (row < 0 || row >= rows || col < 0 || col >= cols) return -1; // Hors limites
    return row * cols + col;
}


int main()
{ 
        sf::ContextSettings settings;
        settings.antialiasingLevel = 8;

        // Charger les textures pour les briques
        Brick::loadTextures();
        sf::Texture backgroundT;
        backgroundT.loadFromFile("mondstadt.png");
        sf::Sprite background;
        background.setTexture(backgroundT);
        Vector2 screenSize(600, 800);
        sf::RenderWindow window(sf::VideoMode(screenSize.x, screenSize.y), "Genshin Bricks", sf::Style::Default, settings);

        sf::Color Anemo(116, 194, 168, 255);
        sf::Color Electro(167, 86, 204, 255);
        sf::Color Pyro(239, 121, 56, 255);
        sf::Color eleStorage[] = { Anemo, Electro, Pyro };

        sf::Font font;
        if (!font.loadFromFile("zh-cn.ttf")) {
            std::cerr << "Error loading font\n";
            return -1;
        }


        float brickWidth = 60.0f;
        float brickHeight = 30.0f;
        float paddingx = 10.0f;
        float paddingy = 40.f;

        vector<string> layout = {
            "aeaeappe",
            "apaeepaa",
            "epapeeep",
            "pppaeeee",
            "eappaepe"
        };
        int rows = layout.size();
        int cols = layout[0].size();
        vector<Brick> bricks;

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

        // Création des briques en grille
        // Adjust brick positions based on layout and add to vector
        for (int row = 0; row < rows; ++row) {
            for (int col = 0; col < cols; ++col) {
                char brickType = layout[row][col];
                if (brickType == '-') continue;
                Vector2 position((brickWidth + paddingx) * col + 20, (brickHeight + paddingy) * row);
                Brick brick;
                sf::Color element = (row % 2 == 0) ? Electro : Anemo;
                brick.init(element, position, Vector2(brickWidth, brickHeight));
                switch (brickType) {
                case 'a': brick.init(Anemo, position, Vector2(brickWidth, brickHeight)); break;
                case 'e': brick.init(Electro, position, Vector2(brickWidth, brickHeight)); break;
                case 'p': brick.init(Pyro, position, Vector2(brickWidth, brickHeight)); break;
                }
                bricks.push_back(brick);
            }
        }

        float ballSize = 10.0f;
        float paddleSize = 100.0f;
        sf::CircleShape Ball(ballSize);
        sf::RectangleShape Paddle(sf::Vector2f(paddleSize, 30));
        Vector2 ballStartPos(300, 400);
        Vector2 ballPos(300, 400);
        Vector2 speed(500.0f, 500.0f);
        sf::Vector2i mousePosition = sf::Mouse::getPosition();
        sf::Clock gameClock;
        sf::Time electroDur;
        sf::Time electroDuration;
        bool electroSpeed = false;
        bool electroSpeedEnhanced = false;
        bool ballVisible = true;
        int lives(3);
        int bricksPerRow = 8;
        Ball.setFillColor(Anemo);
        Ball.setPosition(ballPos.x, ballPos.y);
        Paddle.setPosition(250, 750);  // Centrer la raquette
        vector<string>textStorage = { "lynette.png", "raiden.png", "hutao.png" };
        int eleSwitcher(0);
        sf::Texture paddleTexture;
        if (!paddleTexture.loadFromFile(textStorage[eleSwitcher])) {
            cerr << "Erreur de chargement de la texture " << textStorage[eleSwitcher] << endl;
            return -1; // Quitter si la texture ne se charge pas
        }
        Paddle.setTexture(&paddleTexture);
        sf::Text text;
        sf::Time deltaTime;
        sf::Clock frameClock;
        float newPaddlePosX = mousePosition.x - paddleSize / 2;

        while (window.isOpen())
        {
            deltaTime = frameClock.restart();
            sf::FloatRect paddleBox = Paddle.getGlobalBounds();
            sf::FloatRect ballBox = Ball.getGlobalBounds();
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();
                if (event.type == sf::Event::MouseButtonPressed) {
                    if (event.mouseButton.button == sf::Mouse::Left) {
                        switch (gameState) {
                        case Running:
                            std::cout << "Running left click registered" << std::endl;
                            eleSwitcher = (eleSwitcher + 1) % textStorage.size(); // Passer à la texture suivante
                            if (!paddleTexture.loadFromFile(textStorage[eleSwitcher])) {
                                cerr << "Erreur de chargement de la texture " << textStorage[eleSwitcher] << endl;
                            }
                            else {
                                Paddle.setTexture(&paddleTexture); // Assigner la nouvelle texture
                                cout << "Texture changée vers " << textStorage[eleSwitcher] << endl;
                                break;
                            }
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
                            Ball.setPosition(ballStartPos.x, ballStartPos.y); // Reset ball position
                            speed = Vector2(500.0f, 500.0f);
                            lives = 3;
                            ballVisible = true;
                            electroSpeed = false;
                            electroSpeedEnhanced = false;
                            gameState = Running;
                            ballState = Reposition;
                            break;

                        case GameWin:
                            std::cout << "GameWin R registered" << std::endl;
                            Ball.setPosition(ballStartPos.x, ballStartPos.y); // Reset ball position
                            speed = Vector2(500.0f, 500.0f);
                            lives = 3;
                            ballVisible = true;
                            electroSpeed = false;
                            electroSpeedEnhanced = false;
                            gameState = Running;
                            ballState = Reposition;
                            break;
                        }
                    }
                }
            }

            window.clear();

            switch (gameState) {
            case Running:
            {
                switch (ballState)
                {
                case Flying:
                    Ball.move(speed.x * deltaTime.asSeconds(), speed.y * deltaTime.asSeconds());
                    deltaTime = frameClock.restart();
                    if ((Ball.getPosition().x >= (screenSize.x - (ballSize * 2))) || (Ball.getPosition().x <= 0)) {
                        //BallSound.setBuffer(WallHit);
                        //BallSound.play();
                        speed.x *= -1.0f; // Reverse x speed on wall collision
                    }
                    if ((Ball.getPosition().y >= (screenSize.y - (ballSize * 2))) || (Ball.getPosition().y <= 0)) {
                        //BallSound.setBuffer(WallHit);
                        //BallSound.play();
                        speed.y *= -1.0f; // Reverse y speed on wall collision
                    }
                    break;

                case Reposition:
                    Ball.setPosition(mousePosition.x - ballSize, 730);
                    break;
                }


                // Dessiner la balle, la raquette et les briques visibles
                window.draw(background);
                window.draw(Ball);
                window.draw(Paddle);

                for (auto& brick : bricks) {
                    if (brick.is_visible) {
                        window.draw(brick.sprite);
                    }
                }





                if (Ball.getPosition().y >= 770) {
                    lives -= 1;
                    std::cout << lives << std::endl;
                    ballState = Reposition;
                }

                // Déplacement de la balle
                if (lives <= 0)
                {
                    gameState = GameOver;
                }
                if (checkWinCondition(bricks)) {
                    gameState = GameWin; // Transition to GameWin state if all bricks are invisible
                }


                // Déplacer la raquette en fonction de la souris
                mousePosition = sf::Mouse::getPosition(window);
                newPaddlePosX = mousePosition.x - paddleSize / 2;
                newPaddlePosX = max(0.f, min(newPaddlePosX, screenSize.x - paddleSize));
                Paddle.setPosition(newPaddlePosX, 750);

                // Gérer les collisions balle-raquette

                if (electroSpeed) {
                    // Check how much time has passed since electroSpeed was activated
                    electroDuration = gameClock.getElapsedTime();

                    // Check if the duration has exceeded 2 seconds
                    if (electroDuration.asSeconds() >= 2) {
                        // Reset the speed only once after the timer expires
                        if (electroSpeedEnhanced) {
                            speed.x /= 2.0f;
                            speed.y /= 2.0f;
                        }
                        else {
                            speed.x /= 1.5f;
                            speed.y /= 1.5f;
                        }

                        // Reset the Electro effect flags
                        electroSpeed = false;
                        electroSpeedEnhanced = false;
                    }
                }
                if (paddleBox.intersects(ballBox))
                {
                    if (Ball.getPosition().y + ballSize * 2 >= Paddle.getPosition().y) {
                        // Move the ball just above the paddle to avoid hovering
                        Ball.setPosition(Ball.getPosition().x, Paddle.getPosition().y - ballSize * 2);
                        speed.y *= -1.0f; // Reverse y-speed
                        Ball.setFillColor(Paddle.getFillColor());
                        Ball.setFillColor(eleStorage[eleSwitcher]);
                    }
                }

                // Gérer les collisions balle-briques
                for (size_t i = 0; i < bricks.size(); ++i) {
                    Brick& brick = bricks[i];
                    if (brick.is_visible && ballBox.intersects(brick.brickBox)) {
                        speed.y *= -1.0f;
                        if (brick.Element == Electro)
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
                                brick.is_visible = false;
                            }
                        }

                        if (brick.Element == Pyro)
                        {

                            if (Ball.getFillColor() == Electro)
                            {
                                // Rendre invisible la brique touchée et les briques adjacentes
                                cout << i << endl;
                                brick.is_visible = false;

                                // Indices pour les briques adjacentes (haut, gauche, droite)
                                int topIndex = i - cols;
                                cout << topIndex << endl;
                                // Casser les briques adjacentes si elles existent
                                if (topIndex >= 0 && bricks[topIndex].is_visible) bricks[topIndex].is_visible = false;
                            }
                            if (Ball.getFillColor() == Anemo)
                            {
                                brick.is_visible = false;
                                if (i > 8) bricks[i - 8].is_visible = false;

                                if (i - 1 >= 0 && i / bricksPerRow == (i - 1) / bricksPerRow)
                                    bricks[i - 1].is_visible = false;

                                if (i + 1 < bricks.size() && i / bricksPerRow == (i + 1) / bricksPerRow)
                                    bricks[i + 1].is_visible = false;

                                if (i - 2 >= 0 && i / bricksPerRow == (i - 2) / bricksPerRow)
                                    bricks[i - 2].is_visible = false;

                                if (i + 2 < bricks.size() && i / bricksPerRow == (i + 2) / bricksPerRow)
                                    bricks[i + 2].is_visible = false;
                                if (i > 16) bricks[i - 16].is_visible = false;
                            }
                            else
                            {
                                brick.is_visible = false;
                                if (i > cols) bricks[i - 8].is_visible = false;
                                if (i - 1 >= 0 && bricks[i - 1].is_visible) bricks[i - 1].is_visible = false;
                                if (i + 1 >= 0 && bricks[i + 1].is_visible) bricks[i + 1].is_visible = false;
                            }
                            brick.is_visible = false;
                        }

                        if (brick.Element == Anemo)
                        {
                            if (Ball.getFillColor() == Electro)
                            {
                                if (electroSpeed == false) {
                                    electroSpeedEnhanced = true;
                                    electroSpeed = true; // Activate electro speed
                                    speed.x *= 2.0f;     // Double the speed
                                    speed.y *= 2.0f;     // Double the speed
                                    gameClock.restart();
                                }  // Restart the game clock to track this effect duration
                            }
                            if (Ball.getFillColor() == Pyro)
                            {
                                brick.is_visible = false;
                                if (i > 8) bricks[i - 8].is_visible = false;

                                if (i - 1 >= 0 && i / bricksPerRow == (i - 1) / bricksPerRow)
                                    bricks[i - 1].is_visible = false;

                                if (i + 1 < bricks.size() && i / bricksPerRow == (i + 1) / bricksPerRow)
                                    bricks[i + 1].is_visible = false;

                                if (i - 2 >= 0 && i / bricksPerRow == (i - 2) / bricksPerRow)
                                    bricks[i - 2].is_visible = false;

                                if (i + 2 < bricks.size() && i / bricksPerRow == (i + 2) / bricksPerRow)
                                    bricks[i + 2].is_visible = false;
                                if (i > 16) bricks[i - 16].is_visible = false;
                            }
                            brick.is_visible = false;
                        }

                        break;
                    }
                }
                window.display();
                break;
            }
            case GameOver:
                // Display "The abyss claims all." only in GameOver state
                text.setFont(font);
                text.setString("The abyss claims all.");
                text.setCharacterSize(20);
                text.setFillColor(Electro);
                text.setPosition(screenSize.x / 2 - 100, screenSize.y / 2 - 25);
                for (auto& brick : bricks) {
                    brick.is_visible = true;
                }
                window.draw(text);
                window.display();
                break;

            case GameWin:
                // Display "Let the wind guide you!" only in GameWin state
                text.setFont(font);
                text.setString("Let the wind guide you!");
                text.setCharacterSize(20);
                text.setFillColor(Anemo);
                text.setPosition(screenSize.x / 2 - 100, screenSize.y / 2 - 25);
                for (auto& brick : bricks) {
                    brick.is_visible = true;
                }
                window.draw(text);
                window.display();
                break;
            }
        }
    
    return 0;
}