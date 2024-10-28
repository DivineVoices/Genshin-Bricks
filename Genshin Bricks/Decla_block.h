#pragma once
#include "Fct_Gen.h"

class Brick {
	int m_life;
	Vector2 m_dimension;

public:
	//Constructeur
	Brick(int life, Vector2 dimension) : m_life(life), m_dimension(dimension) {};

	//Gets
	int GetLife();
	Vector2 GetDim();
};

class Anemo_Brick : public Brick {
	Vector2 m_direction;
	float m_vitesse;

public:
	//Constructeur
	Anemo_Brick(int life, Vector2 dimension, Vector2 direction, float vitesse) : Brick(life, dimension), m_direction(direction), m_vitesse(vitesse) {};

	//Gets
	Vector2 GetDir();
	float GetVit();
};

class Geo_Brick : public Brick {

public:
	Geo_Brick(int life, Vector2 dimension) : Brick(life, dimension) {};
};

class Pyro_Brick : public Brick {
	Vector2 m_rayon;
	int m_degats;
public:
	//Constructeur
	Pyro_Brick(int life, Vector2 dimension, Vector2 rayon, int degats) : Brick(life, dimension), m_rayon(rayon), m_degats(degats) {};

	//Gets
	Vector2 GetRay();
	int GetDeg();
};