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
	Paddle(Vector2 taille = Vector2 (100,30), Vector2 position = (0,750), int lives = 3, Element element = Anemo) : m_size(taille), m_position(position), m_lives(lives), m_element(element) {};

	//Gets
	Vector2 GetSize();
	Vector2 GetPos();
	int GetLife();
	sf::RectangleShape GetForm();
	Element GetEle();

	//Fcts
	void ResetLife();
	void CreaPad();
	void SwitchEle();
};