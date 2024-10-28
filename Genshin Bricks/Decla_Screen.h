#pragma once
#include "Fct_Gen.h"

class Screen {
	Vector2 m_size;

public:
	//Constructeur
	Screen(Vector2 size = Vector2(600, 800)) : m_size(size) {};

	void Initialisation();

	//Gets
	Vector2 GetSize();

};