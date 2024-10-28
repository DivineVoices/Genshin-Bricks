#pragma once
#include "Fct_Gen.h"

class Ball {
	float m_taille;
	Vector2 m_position;
	Vector2 m_direction;
	float m_vitesse;
	int m_degats;

public:
	//Constructeur
	Ball(float taille,Vector2 position, Vector2 direction, float vitesse, int degats) : m_taille(taille), m_position(position), m_direction(direction), m_vitesse(vitesse), m_degats(degats) {};

	//Gets
	Vector2 GetPos();
	Vector2 GetDir();
	float GetVit();

	//Fcts
};

class Pyro_Ball : public Ball{

public:
	//Constructeur
	Pyro_Ball(int taille, Vector2 position, Vector2 direction, float vitesse, int degats) : Ball(taille, position, direction, vitesse, degats) {};
};