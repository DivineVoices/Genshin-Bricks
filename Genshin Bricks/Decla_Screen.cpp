#include "Decla_Screen.h"

Vector2 Screen::GetSize() {
	return m_size;
}

sf::ContextSettings Screen::Demarrage() {
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	return settings;
}