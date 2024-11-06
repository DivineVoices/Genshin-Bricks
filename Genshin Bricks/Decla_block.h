#pragma once
#include "Fct_Gen.h"

class Brick {
public:
    Vector2 position;
    sf::Color Element;
    bool is_visible;
    sf::Sprite sprite;
    sf::FloatRect brickBox;

    static sf::Texture anemoTexture;
    static sf::Texture electroTexture;
    static sf::Texture pyroTexture;

    Brick() : is_visible(true) {}

    static void loadTextures();

    void init(sf::Color element, Vector2 position, Vector2 size);

};

