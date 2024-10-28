#include "Decla_Screen.h"

Vector2 Screen::GetSize() {
	return m_size;
}

void Screen::Demarrage() {
	sf::ContextSettings settings = Initialisation();
	sf::RenderWindow window(sf::VideoMode(m_size.m_x, m_size.m_y), "Genshin Bricks", sf::Style::Default, settings);
}