#include "Decla_block.h"
using namespace std;
void Brick::loadTextures() {
    if (!anemoTexture.loadFromFile("res/anemo.png")) {
        cerr << "Erreur de chargement de la texture anemo.png" << endl;
    }
    if (!electroTexture.loadFromFile("res/electro.png")) {
        cerr << "Erreur de chargement de la texture electro.png" << endl;
    }
    if (!pyroTexture.loadFromFile("res/pyro.png")) {
        cerr << "Erreur de chargement de la texture pyro.png" << endl;
    }
}
void Brick::init(sf::Color element, Vector2 position, Vector2 size) {
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

    sprite.setPosition(position.m_x, position.m_y);
    sprite.setScale(size.m_x / sprite.getTexture()->getSize().x, size.m_y / sprite.getTexture()->getSize().y);
    brickBox = sprite.getGlobalBounds();
}
