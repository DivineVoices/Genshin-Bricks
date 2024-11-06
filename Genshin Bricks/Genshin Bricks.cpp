#include "Decla_Game.h"
// Initialisation des textures statiques
sf::Texture Brick::anemoTexture;
sf::Texture Brick::electroTexture;
sf::Texture Brick::pyroTexture;
int main() 
{
    //A ne pas toucher
    Screen screen;
    Ball balle;
    Paddle paddle;
    Game game(screen,balle,paddle);

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    // Charger les textures pour les briques et le background
    Brick::loadTextures();
    sf::Texture backgroundT;
    backgroundT.loadFromFile("res/mondstadt.png");
    sf::Sprite background;
    background.setTexture(backgroundT);

    Vector2 windowSize = game.GetScreenSize();
    sf::RenderWindow window(sf::VideoMode(windowSize.m_x, windowSize.m_y), "Genshin Bricks", sf::Style::Default, settings);
    
    if (!game.font.loadFromFile("res/zh-cn.ttf")) {
        std::cerr << "Erreur de chargement de la police\n";
        return -1;
    }
    //Init couleurs
    sf::Color colorAnemo(116, 194, 168, 255);
    sf::Color colorElectro(167, 86, 204, 255);
    sf::Color colorPyro(239, 121, 56, 255);
    sf::Color colorWhite(255, 255, 255, 255);
    sf::Color eleStorage[] = { colorAnemo, colorElectro, colorPyro };

    float brickWidth = 60.0f;
    float brickHeight = 30.0f;
    float paddingx = 10.0f;
    float paddingy = 40.f;

    std::vector<std::string> layout = {
        "aeaeappe",
        "apaeepaa",
        "epapeeep",
        "pppaeeee",
        "eappaepe"
    };
    int rows = layout.size();
    int cols = layout[0].size();
    std::vector<Brick> bricks;
    // Création des briques en grille
    // Adjust brick positions based on layout and add to vector
    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            char brickType = layout[row][col];
            if (brickType == '-') continue;
            Vector2 position((brickWidth + paddingx) * col + 20, (brickHeight + paddingy) * row);
            Brick brick;
            switch (brickType) {
            case 'a': brick.init(colorAnemo, position, Vector2(brickWidth, brickHeight)); break;
            case 'e': brick.init(colorElectro, position, Vector2(brickWidth, brickHeight)); break;
            case 'p': brick.init(colorPyro, position, Vector2(brickWidth, brickHeight)); break;
            }
            bricks.push_back(brick);
        }
    }

    //Init Clock
    sf::Clock gameClock;
    sf::Time electroDur;

    sf::Vector2i mousePosition = sf::Mouse::getPosition();
    sf::Vector2f positionpaddle(0, 750);
    Vector2 speed(0.1f, 0.1f);
    sf::Time electroDuration;
    bool electroSpeed = false;
    bool brickVisible = true;
    bool electroSpeedEnhanced = false;
    bool winCon = false;
    window.setKeyRepeatEnabled(false);

    //Démarrage
    game.SetGameState(Running);

    //Evenements a ne pas toucher
    while (window.isOpen())
    {
        Ball vrballe = game.GetBall();
        vrballe.CreaBall();
        Paddle vrpaddle = game.GetPaddle();
        vrpaddle.CreaPad();
        vrpaddle.SetPos(positionpaddle);
        sf::FloatRect paddleBox = vrpaddle.GetForm().getGlobalBounds();
        sf::FloatRect ballBox = vrballe.GetForm().getGlobalBounds();
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    game.LeftClick();
                }
                if (event.mouseButton.button == sf::Mouse::Right)
                {
                    vrballe.SetBallState(Flying);
                }
            }
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.scancode == sf::Keyboard::Scan::R)
                {
                    switch (game.GetGameState()) {
                    case Running:
                        std::cout << "Running R registered" << std::endl;
                        break;
                    case GameOver:
                        std::cout << "GameOver R registered" << std::endl;
                        game.RestartGame();
                        brickVisible = true;
                        electroSpeed = false;
                        electroSpeedEnhanced = false;
                        winCon = false;
                        break;

                    case GameWin:
                        std::cout << "GameWin R registered" << std::endl;
                        game.RestartGame();
                        electroSpeed = false;
                        electroSpeedEnhanced = false;
                        winCon = false;
                        break;
                    }
                }
            }
        }

        switch (game.GetGameState())
        {
        case Running:
            switch (game.GetBallState())
            {
            case Flying:

                vrballe.MoveBall(screen);

                break;
            case Repositionning:
                
                vrballe.SetPos(Vector2 (mousePosition.x - vrballe.GetSize(), 730));
                break;
            }
            window.clear();
            window.draw(background);  // Dessiner le fond
            window.draw(vrballe.GetForm());  // Dessiner la balle
            window.draw(vrpaddle.GetForm());  // Dessiner la raquette
            for (auto& brick : bricks) {
                if (brick.is_visible) {
                    window.draw(brick.sprite);  // Dessiner les briques
                }
            }
            window.display();
            break;


            if (paddle.GetLife() <= 0)
            {
                game.SetGameState(GameOver);
            }

            if (vrballe.GetPos().m_y >= 770) {
                game.Death();
            }
            mousePosition = sf::Mouse::getPosition(window);

            if (mousePosition.x >= (windowSize.m_x - (vrpaddle.GetSize().m_x / 2))) mousePosition.x = (windowSize.m_x - (vrpaddle.GetSize().m_x / 2));
            if (mousePosition.x <= (vrpaddle.GetSize().m_x / 2)) mousePosition.x = (vrpaddle.GetSize().m_x / 2);

            positionpaddle = sf::Vector2f(mousePosition.x - (vrpaddle.GetSize().m_x / 2), 750);
            vrpaddle.SetPos(positionpaddle);


            if (electroSpeed) {
                // Check how much time has passed since electroSpeed was activated
                electroDuration = gameClock.getElapsedTime();

                // Check if the duration has exceeded 3 seconds
                if (electroDuration.asSeconds() >= 3) {
                    if (electroSpeedEnhanced == 1) {
                        electroSpeed = false; // Reset the speed flag
                        speed.m_x /= 2.0f;      // Reset speed to normal
                        speed.m_y /= 2.0f;      // Reset speed to normal
                    }
                    else {
                        electroSpeed = false; // Reset the speed flag
                        speed.m_x /= 1.5f;      // Reset speed to normal
                        speed.m_y /= 1.5f;
                    }
                }
            }

            if (paddleBox.intersects(ballBox))
            {
                // Calculate the ball's position to ensure it bounces correctly
                if (vrballe.GetPos().m_y + balle.GetSize() * 2 >= vrpaddle.GetPos().m_y) {
                    // Move the ball just above the paddle to avoid hovering
                    vrballe.SetPos(Vector2 (vrballe.GetPos().m_x, vrpaddle.GetPos().m_y - balle.GetSize() * 2));
                    speed.m_y *= -1.0f; // Reverse y-speed
                }
            }

            for (size_t i = 0; i < bricks.size(); ++i) {
                Brick& brick = bricks[i];
                if (brick.is_visible && ballBox.intersects(brick.brickBox)) {
                    speed.m_y *= -1.0f;
                    //if wincon est une commande temporaire pour faire fonctionner le code, pour l'instant j'ai pas une bonne place pour la wincon alors elle est la comme example
                    if (winCon)
                    {
                        game.SetGameState(GameWin);
                    }

                    if (brick.Element == colorElectro)
                    {
                        if (electroSpeed == false) {
                            if (vrballe.GetEle() == Anemo)
                            {
                                electroSpeedEnhanced = true;
                                electroSpeed = true; // Activate electro speed
                                speed.m_x *= 2.0f;     // Double the speed
                                speed.m_y *= 2.0f;     // Double the speed
                                gameClock.restart();  // Restart the game clock to track this effect duration
                            }
                            else
                            {
                                electroSpeedEnhanced = false;
                                electroSpeed = true; // Activate electro speed
                                speed.m_x *= 1.5f;     // Double the speed
                                speed.m_y *= 1.5f;     // Double the speed
                                gameClock.restart();
                            }
                        }
                    }
                    if ((brick.Element == colorElectro && vrballe.GetEle() == Pyro) ||
                        (brick.Element == colorPyro && vrballe.GetEle() == Electro)) {

                        // Rendre invisible la brique touchée et les briques adjacentes
                        std::cout << i << std::endl;
                        brick.is_visible = false;

                        // Indices pour les briques adjacentes (haut, gauche, droite)
                        int topIndex = i - cols;
                        std::cout << topIndex << std::endl;
                        // Casser les briques adjacentes si elles existent
                        if (topIndex >= 0 && bricks[topIndex].is_visible) bricks[topIndex].is_visible = false;
                    }
                    if (brick.Element == colorPyro && vrballe.GetEle() == Pyro)
                    {
                        brick.is_visible = false;
                        if (i > cols) bricks[i - 8].is_visible = false;
                        if (i - 1 >= 0 && bricks[i - 1].is_visible) bricks[i - 1].is_visible = false;
                        if (i + 1 >= 0 && bricks[i + 1].is_visible) bricks[i + 1].is_visible = false;
                    }
                    if ((brick.Element == colorPyro && vrballe.GetEle() == Anemo) || (brick.Element == colorAnemo && vrballe.GetEle() == Pyro))
                    {
                        brick.is_visible = false;
                        if (i > 8) bricks[i - 8].is_visible = false;

                        if (i - 1 >= 0 && i / cols == (i - 1) / cols)
                            bricks[i - 1].is_visible = false;

                        if (i + 1 < bricks.size() && i /cols == (i + 1) / cols)
                            bricks[i + 1].is_visible = false;

                        if (i - 2 >= 0 && i / cols == (i - 2) / cols)
                            bricks[i - 2].is_visible = false;

                        if (i + 2 < bricks.size() && i / cols == (i + 2) / cols)
                            bricks[i + 2].is_visible = false;
                        if (i > 16) bricks[i - 16].is_visible = false;
                    }
                    else {
                        brick.is_visible = false;
                    }
                }
                break;
            }
        case GameOver:
            window.clear();  // Nettoyer la fenêtre avant de dessiner
            window.draw(game.TextGameOver(colorElectro, windowSize, game.font));
            window.display();  // Afficher ce qui a été dessiné
            break;

        case GameWin:
            window.clear();  // Nettoyer la fenêtre avant de dessiner
            window.draw(game.TextGameOver(colorAnemo, windowSize, game.font));
            window.display();  // Afficher ce qui a été dessiné
            break;

        }
        game.UpdateGame(vrballe, vrpaddle);
    }
    return 0;
}