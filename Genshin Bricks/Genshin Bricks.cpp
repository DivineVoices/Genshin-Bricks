#include "Fct_Gen.h"
#include "Decla_ball.h"
#include "Decla_block.h"
#include "Decla_Screen.h"

int main(){
    Screen Window;
    sf::ContextSettings settings = Window.Demarrage();
    Vector2 size = Window.GetSize();
    sf::RenderWindow window(sf::VideoMode(size.m_x, size.m_y), "Genshin Bricks", sf::Style::Default, settings);
    Ball balle(10, (300, 400), (0.1f, 0.1f), 1);
    balle.CreaBall();

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            window.clear();
            window.draw(balle.GetForm());
            window.display();
            balle.MoveBall(Window);
        }
    }
    return 0;
}