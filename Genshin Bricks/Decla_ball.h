#pragma once
#include "Fct_Gen.h"
#include "Decla_Screen.h"

class Ball {
	float m_taille;
	Vector2 m_position;
	Vector2 m_vitesse;
	int m_degats;
	sf::CircleShape m_forme;
	
public:
	//Constructeur
	Ball(float taille, Vector2 position, Vector2 vitesse, int degats) : m_taille(taille), m_position(position), m_vitesse(vitesse), m_degats(degats) {};

	//Gets
	Vector2 GetPos();
	Vector2 GetVit();
	sf::CircleShape GetForm();

	//Fcts
	void CreaBall();
	void MoveBall(Screen window);
};

class Pyro_Ball : public Ball {

public:
	//Constructeur
	Pyro_Ball(float taille, Vector2 position, Vector2 vitesse, int degats) : Ball(taille, position, vitesse, degats) {};
};