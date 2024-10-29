#include "Decla_ball.h"

Vector2 Ball::GetPos() {
	return m_position;
}
Vector2 Ball::GetDir() {
	return m_direction;
}
float Ball::GetVit() {
	return m_vitesse;
}

void Ball::CreaBall() {
	sf::Color Anemo(116, 194, 168, 255);
	sf::CircleShape Balle(m_taille);
	Balle.setFillColor(Anemo);
	Balle.setPosition(m_position.m_x, m_position.m_x);
}