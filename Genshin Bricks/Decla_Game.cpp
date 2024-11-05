#include "Decla_Game.h"

//Gets
Ball Game::GetBall() {
    return m_balle;
}
Paddle Game::GetPaddle() {
    return m_paddle;
}
Vector2 Game::GetScreenSize() {
    return m_screen.GetSize();
}
GameState Game::GetGameState() {
    return m_gamestate;
}
BallState Game::GetBallState() {
    return m_balle.GetBallState();
}

//Sets
void Game::SetGameState(GameState gamestate) {
    m_gamestate = gamestate;
}

//Fcts
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
void Game::RestartGame() {
    m_balle.SetPos(m_balle.GetStartPos());
    m_balle.SetVit(Vector2(0.1f, 0.1f));
    m_paddle.ResetLife();
    m_balle.SetVisible(true);
    m_gamestate = Running;
    m_balle.SetBallState(Repositionning);
}
void Game::Death() {
    m_paddle.SetLife(-1);
    std::cout << m_paddle.GetLife() << std::endl;
    m_balle.SetBallState(Repositionning);
}
void Game::ChangeElement() {
    m_balle.SetElement(m_paddle.GetEle());
}
sf::Text Game::TextGameOver(sf::Color couleur, Vector2 windowSize) {
    sf::Text text;
    sf::Font font = FontInit();

    text.setFont(font);
    text.setString("The abyss claims all.");
    text.setCharacterSize(20);
    text.setFillColor(couleur);
    text.setPosition(windowSize.m_x / 2 - 100, windowSize.m_y / 2 - 25);

    return text;
}
sf::Text Game::TextGameWin(sf::Color couleur, Vector2 windowSize) {
    sf::Text text;
    sf::Font font = FontInit();

    text.setFont(font);
    text.setString("Let the wind guide you!");
    text.setCharacterSize(20);
    text.setFillColor(couleur);
    text.setPosition(windowSize.m_x / 2 - 100, windowSize.m_y / 2 - 25);

    return text;
}