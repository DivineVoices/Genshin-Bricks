#include "Decla_Screen.h"

void Initialisation() {
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
}

Vector2 Screen::GetSize() {
	return m_size;
}