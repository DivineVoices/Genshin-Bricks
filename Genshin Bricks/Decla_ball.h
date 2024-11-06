#pragma once
#include "Fct_Gen.h"
#include "Decla_Screen.h"

class Ball {
	bool m_visible;
	float m_taille;

	Vector2 m_position;
	Vector2 m_startpos;
	Vector2 m_vitesse;

	BallState m_ballstate;
	Element m_element;
	sf::CircleShape m_forme;
	
public:
	//Constructeur
	Ball(float taille = 10, Vector2 position = Vector2(300,400), Vector2 vitesse = Vector2(0.1f, 0.1f), bool visible = true, BallState ballstate = Flying, Element element = Anemo) : m_taille(taille), m_position(position), m_startpos(position), m_vitesse(vitesse), m_visible(visible), m_ballstate(ballstate), m_element(element) {};

	//Gets
	float GetSize();
	Vector2 GetPos();
	Vector2 GetVit();
	sf::CircleShape GetForm();
	bool GetVis();
	Vector2 GetStartPos();
	BallState GetBallState();
	Element GetEle();

	//Sets
	void SetPos(Vector2 V);
	void SetVit(Vector2 V);
	void SetBallState(BallState ballstate);
	void SetVisible(bool visible);
	void SetElement(Element element);

	//Fcts
	void CreaBall();
	void MoveBall(Screen window);
};