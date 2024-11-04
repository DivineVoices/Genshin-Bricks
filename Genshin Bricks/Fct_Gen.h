#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

struct Vector2 {
	float m_x, m_y;
	Vector2(float x = 0, float y = 0) : m_x(x), m_y(y) {}

	Vector2 operator+(const Vector2* i) {
		return Vector2(m_x + i->m_x, m_y + i->m_y);
	}
	Vector2 operator+=(const Vector2* i) {
		return Vector2(m_x += i->m_x, m_y += i->m_y);
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

sf::Font FontInit(){
	sf::Font font;
	if (!font.loadFromFile("zh-cn.ttf")) {
		std::cerr << "Error loading font\n";
	}
	else {
		return font;
	}
}

enum Element {
	Anemo = 1,
	Electro,
	Pyro,
};

enum GameState {
	Starting,
	Running,
	GameOver,
	GameWin,
};

enum BallState {
	Repositionning,
	Flying,
};