#include "Decla_Game.h"

Vector2 Game::GetScreenSize() {
    return m_screen.GetSize();
}
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
BallState Game::GetBallState() {
    return m_balle.GetBallState();
}
void Game::RestartGame() {
    m_balle.SetPos(m_balle.GetStartPos());
    m_balle.SetVit(Vector2(0.1f, 0.1f));
    m_paddle.ResetLife();
    m_balle.SetVisible(true);
    m_gamestate = Running;
    m_balle.SetBallState(Repositionning);
}
Ball Game::GetBall() {
    return m_balle;
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