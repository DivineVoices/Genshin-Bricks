#include "Decla_ball.h"

float Ball::GetSize() {
	return m_taille;
}
Vector2 Ball::GetPos() {
	return m_position;
}
Vector2 Ball::GetVit() {
	return m_vitesse;
}
sf::CircleShape Ball::GetForm() {
	return m_forme;
}
bool Ball::GetVis() {
	return m_visible;
}
Vector2 Ball::GetStartPos() {
	return m_startpos;
}

void Ball::CreaBall() {
	sf::Color White(255, 255, 255, 255);
	sf::CircleShape Balle(m_taille);
	Balle.setFillColor(White);
	Balle.setPosition(m_position.m_x, m_position.m_y);
	m_forme = Balle;
}

void Ball::MoveBall(Screen window) {
	m_position.m_x += m_vitesse.m_x;
	m_position.m_y += m_vitesse.m_y;
	Vector2 screenSize = window.GetSize();
	if ((m_position.m_x >= (screenSize.m_x - (m_taille * 2))) || (m_position.m_x <= 0)) { m_vitesse.m_x *= -1.0f; }
	if ((m_position.m_y >= (screenSize.m_y - (m_taille * 2))) || (m_position.m_y <= 0)) { m_vitesse.m_y *= -1.0f; }
	m_forme.move(m_vitesse.m_x, m_vitesse.m_y);
}

void Ball::SetBallState(BallState ballstate) {
	m_ballstate = ballstate;
}

void Ball::SetPos(Vector2 V) {
	m_position.m_x = V.m_x;
	m_position.m_y = V.m_y;
}

void Ball::SetVit(Vector2 V) {
	m_vitesse.m_x = V.m_x;
	m_vitesse.m_y = V.m_y;
}

void Ball::SetVisible(bool visible) {
	m_visible = visible;
}

BallState Ball::GetBallState() {
	return m_ballstate;
}