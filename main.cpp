#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "personaje.h"
#include "personaje.cpp"
#include "bomba.h"
#include "bomba.cpp"

#include "bloqueBase.h"
#include "bloqueBase.cpp"
#include "bloque.h"
#include "bloqueDestruible.h"
#include "mapaBloques.h"
#include "mapaBloques.cpp"
#include "explosion.h"
#include "explosion.cpp"

#include "configuration.h"
#include "configuration.cpp"

#include <iostream>
#include <thread>
#include <future>

int main()
{
    
    //ventana
    sf::RenderWindow window(sf::VideoMode(680, 680), "BOMBERMAN");

    //cargar imagen
    //personaje p(1);
    //personaje p2(2);
    
    //crear objeto

    std::shared_ptr<personaje> p = std::make_shared<personaje>(1);
    std::shared_ptr<personaje> p2 = std::make_shared<personaje>(2);
    std::shared_ptr<mapaBloques> mapa = std::make_shared<mapaBloques>();

    //Bucle de juego
    sf::Clock clock;
    sf::Time time;
    sf::Time actualTime;

    //Creacion del hilo en segundo plano MUSIC
    sf::Music music;
    music.openFromFile("imagenes/musica.mp3");
    std::thread thread(&sf::Music::play, &music);

    //crear objeto por SINGLETON
    configuration &config = configuration::getInstance(clock);
    
    while (window.isOpen())
    {   
        sf::Event event;
        actualTime = clock.getElapsedTime();
        window.clear();

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            
        }

        int estado = config.getState();

        if (estado == -1)
        {
            config.inicio(window, event, actualTime);
            config.resetLives();
            
        }
        else if (estado == 0)
        {       
            
            //std::cout << "entra al juego" << std::endl;
            mapa->dibujarMapa(window);
            config.drawLife(window);

            p->explosionSequence(event, clock, window, mapa, p2);
            p2->explosionSequence(event, clock, window, mapa, p);

            window.draw(p->dibujar());
            //window.draw(p->dibujarBase());
            //window.draw(p->dibujar());

            window.draw(p2->dibujar());
            //window.draw(p2->dibujarBase());
            //window.draw(p2->dibujar());

            if (event.key.code == sf::Keyboard::Escape)
            {   
                config.setState(-1);
                //p->setBasePosicion(sf::Vector2f(80.f, 80.f));
                //p2->setBasePosicion(sf::Vector2f(80.f, 80.f));
                p.reset();
                p = std::make_shared<personaje>(1);
                p2.reset();
                p2 = std::make_shared<personaje>(2);

                mapa.reset();
                mapa = std::make_shared<mapaBloques>();
            }

            if (p->getColisionState())
            {
                config.reduceVida1();

                p.reset();
                p = std::make_shared<personaje>(1);
                p2.reset();
                p2 = std::make_shared<personaje>(2);

                mapa.reset();
                mapa = std::make_shared<mapaBloques>();
            }
            
            if (p2->getColisionState())
            {
                config.reduceVida2();

                p.reset();
                p = std::make_shared<personaje>(1);
                p2.reset();
                p2 = std::make_shared<personaje>(2);

                mapa.reset();
                mapa = std::make_shared<mapaBloques>();
            }

            if (config.getLessLife()<=0)
            {
                config.setState(1);
                time = clock.getElapsedTime();

                p.reset();
                p = std::make_shared<personaje>(1);
                p2.reset();
                p2 = std::make_shared<personaje>(2);

                mapa.reset();
                mapa = std::make_shared<mapaBloques>();
            }
        }
        else if(estado == 1)
        {
            config.winner(window);
            actualTime = clock.getElapsedTime();
            if (actualTime.asMilliseconds() > time.asMilliseconds() + 3000)
            {
                config.setState(-1);
            }

        }
        
        window.display();
        
    }
    


    return 0;
}