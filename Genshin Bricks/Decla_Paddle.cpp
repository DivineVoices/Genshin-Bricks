#include "Decla_Paddle.h"

//Gets
int Paddle::GetLife() {
	return m_lives;
}
Vector2 Paddle::GetSize() {
	return m_size;
}
Vector2 Paddle::GetPos() {
	return m_position;
}
sf::RectangleShape Paddle::GetForm() {
	return m_forme;
}
Element Paddle::GetEle() {
	return m_element;
}

//Sets
void Paddle::SetLife(int i) {
	m_lives += i;
}
void Paddle::SetPos(sf::Vector2f V) {
	m_forme.setPosition(V);
}

//Fcts
void Paddle::ResetLife() {
	m_lives = 3;
}
void Paddle::CreaPad() {
	sf::RectangleShape Paddle(sf::Vector2f(m_size.m_x, m_size.m_y));
	m_forme = Paddle;
}
void Paddle::SwitchEle() {
	switch (m_element) {
	case 1:
		m_element = Electro;
		if (!texture.loadFromFile("res/raiden.png")) {
			std::cerr << "Erreur de chargement de la texture " << std::endl;
		}
		m_forme.setTexture(&texture);
		break;
	case 2:
		m_element = Pyro;
		if (!texture.loadFromFile("res/hutao.png")) {
			std::cerr << "Erreur de chargement de la texture " << std::endl;
		}
		m_forme.setTexture(&texture);
		break;
	case 3:
		m_element = Anemo;
		if (!texture.loadFromFile("res/lynette.png")) {
			std::cerr << "Erreur de chargement de la texture " << std::endl;
		}
		m_forme.setTexture(&texture);
		break;
	}
}

