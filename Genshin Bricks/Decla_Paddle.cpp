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

void Paddle::CreaPad() {
	sf::Color White(255, 255, 255, 255);
	sf::RectangleShape Paddle(sf::Vector2f(m_size.m_x, m_size.m_y));
	Paddle.setFillColor(White);
	m_forme = Paddle;
}
void Paddle::SwitchEle() {

}