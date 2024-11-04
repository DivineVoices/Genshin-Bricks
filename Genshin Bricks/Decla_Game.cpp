#include "Decla_Game.h"

void Game::Init() {
    sf::ContextSettings settings = m_Window.Demarrage();
    Vector2 windowSize = m_Window.GetSize();
    sf::RenderWindow window(sf::VideoMode(windowSize.m_x, windowSize.m_y), "Genshin Bricks", sf::Style::Default, settings);
    sf::Font font = FontInit();

    m_balle.CreaBall();
    m_paddle.CreaPad();
}