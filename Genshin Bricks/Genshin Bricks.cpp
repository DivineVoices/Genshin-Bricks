#include "Fct_Gen.h"
#include "Decla_ball.h"
#include "Decla_block.h"
#include "Decla_Screen.h"

int main()
{
    void Demarrage();

    Ball balle(10, (300, 400), (1, 1), 2, 1);
    balle.CreaBall();

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed){
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
        
        
        ballPos.m_x += speed.m_x;
        ballPos.m_y += speed.m_y;
        if ((ballPos.m_x >= (screenSize.m_x - (ballSize*2))) || (ballPos.m_x <= 0)) speed.m_x *= -1.0f;
        if ((ballPos.m_y >= (screenSize.m_y - (ballSize*2))) || (ballPos.m_y <= 0)) speed.m_y *= -1.0f;
        shape.move(speed.m_x, speed.m_y);

        
    }*/

    return 0;
}
