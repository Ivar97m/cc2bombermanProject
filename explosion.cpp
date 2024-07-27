#include "explosion.h"

explosion::explosion()
{
    bom = nullptr;
    bombaState = false;
}

void explosion::setTime(sf::Clock clock)
{
    time = clock.getElapsedTime();
}

bool explosion::getBombaState()
{
    return bombaState;
}

bool explosion::colision(sf::RectangleShape &per)
{

    if (bom->colision(per, bombDisplay)==true)
    {
        //per.setPosition(sf::Vector2f(80.f, 80.f)); //devuelve al personaje al principio
        return true;
    }
    return false;
}

void explosion::deleteBomba(sf::Clock clock, sf::RenderWindow &window, std::shared_ptr<mapaBloques> mapa, sf::RectangleShape &per)
{
    actualTime = clock.getElapsedTime();
    sf::RectangleShape base = per;

    if (bom == nullptr)
    {   
        float x = floor(base.getPosition().x / 40.f) * 40.f;
        float y = floor(base.getPosition().y / 40.f) * 40.f;
        bom = new bomba(sf::Vector2f(x, y), clock);
        //bom->setPosition(base.getPosition());
        std::cout << "bomba creada" << std::endl;
        bombaState = true;
        
    }

    bom->explosionBomba(clock);
    window.draw(bom->dibujarBombita());

    if (bom->dibujarExplosion() != nullptr)
    {
        if (arrExplosion == nullptr)
        {
            arrExplosion = bom->dibujarExplosion();
            int size = sizeof(arrExplosion)/sizeof(arrExplosion[0]);   //error, no calcula correctamente el tamaño
            //std::cout << size << std::endl; //no funciona esto 
            for (int i = 0; i < 5; i++)
            {   
                for (int j = 0; j < 2; j++)
                {
                    if(mapa->colision(arrExplosion[5*j + i])) break;

                    if(mapa->colisionBloque(arrExplosion[5*j + i]))
                    {
                        mapa->setPosition(arrExplosion[5*j + i], window);  
                        bombDisplay[5*j + i] = 1;                      
                        break;
                    }

                    window.draw(arrExplosion[5*j + i]);
                    bombDisplay[5*j + i] = 1;
                }
            }
        }

        for (int i = 0; i < 10; i++)
        {   
            if (bombDisplay[i] == 1)
            {
                window.draw(arrExplosion[i]);
            }
        }
                
    }
    
    if (actualTime.asMilliseconds() >= 4e3 + time.asMilliseconds())
    {
        //std::cout << "2" << std::endl;
        //delete[] bom;         Porque hay error en esta parte??? 
        bom = nullptr;
        arrExplosion = nullptr;
        bombaState = false;
        std::cout << "bomba destruida" << std::endl;
        for(int i=0; i<10; i++) bombDisplay[i] = 0;
        
    }
    
}



