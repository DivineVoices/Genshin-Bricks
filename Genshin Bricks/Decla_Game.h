#pragma once
#include "Fct_Gen.h"
#include "Decla_ball.h"
#include "Decla_block.h"
#include "Decla_Screen.h"
#include "Decla_Paddle.h"

//Constantes




//Game
class Game {
	Screen m_Window;
	GameState m_gamestate = Starting;

	//Constantes
	Ball m_balle;
	Paddle m_paddle;
public:
	Game(Screen Window, Ball balle, Paddle paddle) : m_Window(Window), m_balle(balle), m_paddle(paddle) {};

	void Init();
};