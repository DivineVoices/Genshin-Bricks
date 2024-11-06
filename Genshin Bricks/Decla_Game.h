#pragma once
#include "Fct_Gen.h"
#include "Decla_ball.h"
#include "Decla_block.h"
#include "Decla_Screen.h"
#include "Decla_Paddle.h"

class Game {
	//Objets
	Screen m_screen;
	Ball m_balle;
	Paddle m_paddle;

	//Variables
	GameState m_gamestate = Starting;

public:
	//Constructeur
	Game(Screen screen, Ball balle, Paddle paddle) : m_screen(screen), m_balle(balle), m_paddle(paddle) {};

	//Gets
	Ball GetBall();
	Paddle GetPaddle();
	Vector2 GetScreenSize();
	GameState GetGameState();
	BallState GetBallState();

	//Sets
	void SetGameState(GameState gamestate);
	void UpdateGame(Screen screen, Ball balle, Paddle paddle);

	//Fcts
    void Init();
	void LeftClick();
	void RestartGame();
	void Death();
	void ChangeElement(sf::Color elestorage[]);
	sf::Text TextGameOver(sf::Color couleur, Vector2 windowSize, sf::Font font);
	sf::Text TextGameWin(sf::Color couleur, Vector2 windowSize, sf::Font font);
};