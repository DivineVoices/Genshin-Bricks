#pragma once
#include "Fct_Gen.h"
#include "Decla_Screen.h"

class Ball {
	float m_taille;
	Vector2 m_position;
	Vector2 m_vitesse;
	int m_degats;
	sf::CircleShape m_forme;
	bool m_visible;
	BallState m_ballstate = Repositionning;
	
public:
	//Constructeur
	Ball(float taille = 10, Vector2 position = Vector2(300,400), Vector2 vitesse = Vector2 (0.1f,0.1f), int degats = 1, bool visible = true) : m_taille(taille), m_position(position), m_vitesse(vitesse), m_degats(degats), m_visible(visible) {};

	//Gets
	float GetSize();
	Vector2 GetPos();
	Vector2 GetVit();
	sf::CircleShape GetForm();
	bool GetVis();

	//Fcts
	void CreaBall();
	void MoveBall(Screen window);
	
};

class Pyro_Ball : public Ball {

public:
	//Constructeur
	Pyro_Ball(float taille, Vector2 position, Vector2 vitesse, int degats) : Ball(taille, position, vitesse, degats) {};
};