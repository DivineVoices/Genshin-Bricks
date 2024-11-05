#include "Decla_Paddle.h"

Vector2 Paddle::GetSize() {
	return m_size;
}
Vector2 Paddle::GetPos() {
	return m_position;
}
int Paddle::GetLife() {
	return m_lives;
}
sf::RectangleShape Paddle::GetForm() {
	return m_forme;
}
Element Paddle::GetEle() {
	return m_element;
}

void Paddle::ResetLife() {
	m_lives = 3;
}
void Paddle::CreaPad() {
	sf::Color White(255, 255, 255, 255);
	sf::RectangleShape Paddle(sf::Vector2f(m_size.m_x, m_size.m_y));
	Paddle.setFillColor(White);
	m_forme = Paddle;
}
void Paddle::SwitchEle() {
	switch (m_element) {
	case 1:
		m_element = Electro;
		m_forme.setFillColor(sf::Color (167, 86, 204, 255));
		break;
	case 2:
		m_element = Pyro;
		m_forme.setFillColor(sf::Color(239, 121, 56, 255));
		break;
	case 3:
		m_element = Anemo;
		m_forme.setFillColor(sf::Color(116, 194, 168, 255));
		break;
	}
}

void Paddle::SetLife(int i) {
	m_lives += i;
}
void Paddle::SetPos(Vector2 V) {
	m_position.m_x = V.m_x;
	m_position.m_y = V.m_y;
}