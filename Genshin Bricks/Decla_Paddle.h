#pragma once
#include "Fct_Gen.h"

class Paddle {
	Vector2 m_size;
	int m_lives;
public:
	//Constructeur
	Paddle(Vector2 taille, int lives) : m_size(taille), m_lives(lives) {};

	//Gets
	Vector2 GetSize();
	int GetLife();
};