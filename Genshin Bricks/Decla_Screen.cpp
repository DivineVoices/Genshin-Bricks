#include "Decla_Screen.h"

Vector2 Screen::GetSize() {
	return m_size;
}

void Screen::Demarrage() {
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
}