#include <iostream>
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Window/Mouse.hpp>

using namespace std;

struct Vector2 {
    float x, y;
    Vector2(float _x = 0, float _y = 0) : x(_x), y(_y) {}
};

class Brick
{
public:
    Vector2 position;
    string Element;
    bool is_visible;
    sf::FloatRect brickBox;
    sf::Texture texture;
    sf::Sprite sprite;

    Brick() : is_visible(true) {}

    void init(string element, Vector2 position, Vector2 size)
    {
        this->position = position;
        this->Element = element;
        is_visible = true;

        if (Element == "Pyro") {
            texture.loadFromFile("pyro.png");
        }
        else if (Element == "Anemo") {
            texture.loadFromFile("anemo.png");
        }
        else if (Element == "Electro") {
            texture.loadFromFile("electro.png");
        }

        sprite.setTexture(texture);
        sprite.setPosition(position.x, position.y);
        sprite.setScale(size.x / texture.getSize().x, size.y / texture.getSize().y); // Mise à l'échelle
        brickBox = sprite.getGlobalBounds();  // Mettre à jour le rectangle de collision
    }
};

int main()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    Vector2 screenSize(600, 800);
    sf::RenderWindow window(sf::VideoMode(screenSize.x, screenSize.y), "Genshin Bricks", sf::Style::Default, settings);

    sf::Color Anemo(116, 194, 168, 255);
    sf::Color Geo(253, 178, 12, 255);
    sf::Color Pyro(239, 121, 56, 255);

    float brickWidth = 60.0f;
    float brickHeight = 30.0f;
    float padding = 10.0f;

    vector<Brick> bricks;
    int rows = 5;   // Nombre de lignes
    int cols = 8;   // Nombre de colonnes

    // Créer les briques en grille
    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            Vector2 position((brickWidth + padding) * col, (brickHeight + padding) * row);
            Brick brick;
            string element = (row % 2 == 0) ? "Anemo" : "Pyro";  // Alterner les éléments pour l'exemple
            brick.init(element, position, Vector2(brickWidth, brickHeight));
            bricks.push_back(brick);
        }
    }

    float ballSize = 10.0f;
    float paddleSize = 100.0f;
    sf::CircleShape Ball(ballSize);
    sf::RectangleShape Paddle(sf::Vector2f(paddleSize, 30));
    sf::Vector2i mousePosition = sf::Mouse::getPosition();

    Vector2 ballPos(300, 400);
    Vector2 speed(0.1f, 0.1f);

    Ball.setFillColor(Anemo);
    Paddle.setFillColor(Geo);
    Ball.setPosition(ballPos.x, ballPos.y);
    Paddle.setPosition(0, 750);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(Ball);
        window.draw(Paddle);

        // Dessiner toutes les briques visibles
        for (auto& brick : bricks) {
            if (brick.is_visible) {
                window.draw(brick.sprite);
            }
        }

        window.display();

        ballPos.x += speed.x;
        ballPos.y += speed.y;

        // Inverser la direction de la balle si elle touche les bords de l'écran
        if ((ballPos.x >= (screenSize.x - (ballSize * 2))) || (ballPos.x <= 0)) speed.x *= -1.0f;
        if ((ballPos.y >= (screenSize.y - (ballSize * 2))) || (ballPos.y <= 0)) speed.y *= -1.0f;

        Ball.move(speed.x, speed.y);

        // Déplacer la raquette en fonction de la position de la souris
        mousePosition = sf::Mouse::getPosition(window);
        if (mousePosition.x >= (screenSize.x - (paddleSize / 2))) mousePosition.x = (screenSize.x - (paddleSize / 2));
        if (mousePosition.x <= (paddleSize / 2)) mousePosition.x = (paddleSize / 2);
        Paddle.setPosition(mousePosition.x - (paddleSize / 2), 750);

        sf::FloatRect paddleBox = Paddle.getGlobalBounds();
        sf::FloatRect ballBox = Ball.getGlobalBounds();

        // Collision entre la balle et la raquette
        if (paddleBox.intersects(ballBox))
        {
            speed.y *= -1.0f;
            Ball.setFillColor(Pyro);
        }

        // Collision entre la balle et les briques
        for (auto& brick : bricks) {
            if (brick.is_visible && ballBox.intersects(brick.brickBox)) {
                float overlapLeft = ballBox.left + ballBox.width - brick.brickBox.left;
                float overlapRight = brick.brickBox.left + brick.brickBox.width - ballBox.left;
                float overlapTop = ballBox.top + ballBox.height - brick.brickBox.top;
                float overlapBottom = brick.brickBox.top + brick.brickBox.height - ballBox.top;

                bool collisionFromLeft = (overlapLeft < overlapRight) && (overlapLeft < overlapTop) && (overlapLeft < overlapBottom);
                bool collisionFromRight = (overlapRight < overlapLeft) && (overlapRight < overlapTop) && (overlapRight < overlapBottom);
                bool collisionFromTop = (overlapTop < overlapBottom) && (overlapTop < overlapLeft) && (overlapTop < overlapRight);
                bool collisionFromBottom = (overlapBottom < overlapTop) && (overlapBottom < overlapLeft) && (overlapBottom < overlapRight);

                if (collisionFromLeft || collisionFromRight)
                {
                    speed.x *= -1.0f;
                }
                if (collisionFromTop || collisionFromBottom)
                {
                    speed.y *= -1.0f;
                }

                brick.is_visible = false;
                break;
            }
        }
    }

    return 0;
}
