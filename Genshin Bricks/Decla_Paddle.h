#pragma once
#include "Fct_Gen.h"

class Paddle {
	Vector2 m_size;
	Vector2 m_position;
	int m_lives;
	sf::RectangleShape m_forme;
	Element m_element;

public:
	//Constructeur
	Paddle(Vector2 taille, Vector2 position, int lives) : m_size(taille), m_position(position), m_lives(lives) {};

	//Gets
	Vector2 GetSize();
	Vector2 GetPos();
	int GetLife();
	sf::RectangleShape GetForm();

	//Fcts
	void CreaPad();
	void SwitchEle();
};