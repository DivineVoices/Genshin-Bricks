#include "Fct_Gen.h"
#include "Decla_ball.h"
#include "Decla_block.h"
#include "Decla_Screen.h"

int main(){
    //A ne pas toucher
    Screen Window;
    sf::ContextSettings settings = Window.Demarrage();
    Vector2 size = Window.GetSize();
    sf::RenderWindow window(sf::VideoMode(size.m_x, size.m_y), "Genshin Bricks", sf::Style::Default, settings);
    //A partir de là, c'est bon

    //Création de balles
    Ball balle(10, (300, 400),Vector2 (0.1f, 0.5f), 1);


    //Initialisation de Ball
    balle.CreaBall();

    //Evenements a ne pas toucher
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear();
        window.draw(balle.GetForm());
        window.display();
        //Modifiable à partir d'ici


        balle.MoveBall(Window);
    }
    return 0;
}