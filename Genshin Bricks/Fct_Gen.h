#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

void Initialisation() {
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
}

//Définitions des couleurs
sf::Color White(255, 255, 255, 255);
sf::Color Anemo(116, 194, 168, 255);
sf::Color Geo(253, 178, 12, 255);
sf::Color Pyro(239, 121, 56, 255);

struct Vector2 {
	float m_x, m_y;
	Vector2(float x = 0, float y = 0) : m_x(x), m_y(y) {}

	Vector2 operator+(const Vector2* i) {
		return Vector2(m_x + i->m_x, m_y + i->m_y);
	}
	Vector2 operator-(const Vector2* i) {
		return Vector2(m_x - i->m_x, m_y - i->m_y);
	}
	Vector2 operator*(const Vector2* i) {
		return Vector2(m_x * i->m_x, m_y * i->m_y);
	}
	Vector2 operator*(const float i) {
		return Vector2(m_x * i, m_y * i);
	}
};