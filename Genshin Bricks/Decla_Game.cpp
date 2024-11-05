#include "Decla_Game.h"

void Game::Init() {
    m_balle.CreaBall();
    m_paddle.CreaPad();
}
void Game::LeftClick() {
    std::cout << "Left click registered" << std::endl;
    switch (m_gamestate) {
    case Starting:
        std::cout << "Starting left click registered" << std::endl;
        break;
    case Running:
        m_paddle.SwitchEle();

    case GameOver:
        std::cout << "GameOver left click registered" << std::endl;
        break;

    case GameWin:
        std::cout << "GameWin left click registered" << std::endl;
        break;
    }
}
void Game::SetGameState(GameState gamestate) {
    m_gamestate = gamestate;
}
GameState Game::GetGameState() {
    return m_gamestate;
}

void Game::RestartGame() {
    m_balle.SetPos()
}