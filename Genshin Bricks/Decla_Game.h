#pragma once
#include "Fct_Gen.h"
#include "Decla_ball.h"
#include "Decla_block.h"
#include "Decla_Screen.h"
#include "Decla_Paddle.h"

//Constantes

//Game
class Game {
	Screen m_screen;
	GameState m_gamestate = Starting;

	//Constantes
	Ball m_balle;
	Paddle m_paddle;
public:
	Game(Screen screen, Ball balle, Paddle paddle) : m_screen(screen), m_balle(balle), m_paddle(paddle) {};

	Vector2 GetScreenSize();
    void Init();
	void LeftClick();
	void SetGameState(GameState gamestate);
	void RestartGame();
	GameState GetGameState();

	sf::Text TextGameOver(sf::Color couleur, Vector2 windowSize);
	sf::Text TextGameWin(sf::Color couleur, Vector2 windowSize);
};