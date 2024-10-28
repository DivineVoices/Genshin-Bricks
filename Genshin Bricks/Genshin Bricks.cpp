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
    sf::Color Geo(253, 178, 12, 255);
    sf::Color Pyro(239, 121, 56, 255);
    float ballSize(10);
    float paddleSize(100);
    sf::CircleShape Ball(ballSize);
    sf::RectangleShape Paddle(sf::Vector2f(paddleSize, 30));
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
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

        // Mise à jour des positions et des limites
        ballPos.x += speed.x;
        ballPos.y += speed.y;
        Ball.setPosition(ballPos.x, ballPos.y); // Mise à jour de la position du cercle
        sf::FloatRect boundingball = Ball.getGlobalBounds(); // Mettre à jour après avoir déplacé Ball
        sf::FloatRect boundingpaddle = Paddle.getGlobalBounds(); // Mettre à jour pour détecter la position actuelle de la raquette

        // Vérification des collisions avec les bords de l'écran
        if ((ballPos.x >= (screenSize.x - (ballSize * 2))) || (ballPos.x <= 0)) speed.x *= -1.0f;
        if ((ballPos.y >= (screenSize.y - (ballSize * 2))) || (ballPos.y <= 0)) speed.y *= -1.0f;

        // Vérification des collisions avec la raquette
        if (boundingball.intersects(boundingpaddle)) {
            speed.y *= -1.0f; // Rebond vertical
        }

        // Suivi de la souris pour la raquette
        mousePosition = sf::Mouse::getPosition(window);
        if (mousePosition.x >= (screenSize.x - (paddleSize / 2))) mousePosition.x = (screenSize.x - (paddleSize / 2));
        if (mousePosition.x <= (paddleSize / 2)) mousePosition.x = (paddleSize / 2);
        Paddle.setPosition(mousePosition.x - (paddleSize / 2), 750);

        // Affichage de la scène
        window.clear();
        window.draw(Ball);
        window.draw(Paddle);
        window.display();

        std::cout << "current mouse position is : " << mousePosition.x << std::endl;
    }

    return 0;
}
