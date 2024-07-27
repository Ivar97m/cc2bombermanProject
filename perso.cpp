#ifndef _BOMBERMAN_
#define _BOMBERMAN_

#include <SFML/Graphics.hpp>
#include "bomba.h"
#include "mapaBloques.h"
#include "explosion.h"


#include <cmath>
#include <memory>
#include <vector>

class personaje
{
    private:
        sf::Vector2f posicion;
        sf::Texture texture;
        sf::Sprite p1;
        sf::RectangleShape base;
        sf::Time time;
        sf::Time actualTime;

        bomba *bom;
        bool bombaState;

        int bombDisplay[10] = {0}; //cuidado

        sf::RectangleShape *arrExplosion = nullptr;

        //float timebom;
        //int numBom = 2;
        std::vector<std::unique_ptr<explosion>> explo;

        float speed;

    public:
        personaje();
        personaje(sf::Texture, sf::Vector2f);
        sf::Sprite& dibujar();
        sf::RectangleShape& dibujarBase();
        void mover(sf::Event);
        void setSpeed(float speed);
        void setPosicion();
        void setSpritePosition();

        //void deleteBomba(sf::Clock, sf::RenderWindow &, mapaBloques &);

        //bool getBombaState();
        sf::Vector2f getPosicion();
        //void setTime(sf::Clock);
        //void colision();
        void colisionPosition(sf::Event, mapaBloques &);

        std::vector<std::unique_ptr<explosion>>& getExplosion();

};

#endif


#include "personaje.h"

#include <iostream>

personaje::personaje()
{   
    texture.loadFromFile("imagenes/bomberman.png");
    p1.setTexture(texture);
    p1.setPosition(sf::Vector2f(40.f, 40.f));
    bom = nullptr;
    bombaState = false;
    
    base.setSize(sf::Vector2f(24.f, 24.f));
    base.setPosition(sf::Vector2f(80, 80));

    for(int i=0; i<2; i++) explo.push_back(std::make_unique<explosion>());

    speed = 0.25f;
}

personaje::personaje(sf::Texture texture_, sf::Vector2f v) : posicion(v)
{
    p1.setPosition(posicion);
    p1.setTexture(texture_);
}

sf::Sprite& personaje::dibujar()
{
    return p1;
}

sf::RectangleShape& personaje::dibujarBase()
{
    return base;
}

void personaje::mover(sf::Event key)
{
    if (key.key.code == sf::Keyboard::Left)
    {
        base.move(-speed, 0);
    }
    else if (key.key.code == sf::Keyboard::Right)
    {
        base.move(speed, 0);
    }
    else if (key.key.code == sf::Keyboard::Down)
    {
        base.move(0, speed);
    }
    else if (key.key.code == sf::Keyboard::Up)
    {
        base.move(0, -speed);
    }
    //p1.setPosition(base.getPosition());
    //std::cout << p1.getGlobalBounds().left << " ";
    //std::cout << p1.getGlobalBounds().top << " " << std::endl;
    //std::cout << p1.getPosition().x << " " << std::endl;
    
}

void personaje::setSpeed(float speed_)
{
    speed = speed_;
}

void personaje::setPosicion()
{
    p1.setPosition(base.getPosition());
}

bool personaje::getBombaState()
{
    return bombaState;
}

sf::Vector2f personaje::getPosicion()
{
    return base.getPosition();
}

void personaje::setTime(sf::Clock clock)
{
    time = clock.getElapsedTime();
}

void personaje::deleteBomba(sf::Clock clock, sf::RenderWindow &window, mapaBloques &mapa)
{
    actualTime = clock.getElapsedTime();
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
    window.draw(bom->dibujarBomba());

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
                    if(mapa.colision(arrExplosion[5*j + i])) break;

                    if(mapa.colisionBloque(arrExplosion[5*j + i]))
                    {
                        mapa.setPosition(arrExplosion[5*j + i], window);  
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

void personaje::colision()
{
    if (bom->colision(base, bombDisplay)==true)
    {
        base.setPosition(sf::Vector2f(80.f, 80.f)); //devuelve al personaje al principio
    }
    
}

void personaje::colisionPosition(sf::Event event, mapaBloques &mapa)
{
    if (event.type == sf::Event::KeyPressed)
    {
        sf::Vector2f posicionActual = base.getPosition();
        sf::Vector2f nuevaPosicion = posicionActual;

        // Determina la nueva posición basada en la entrada del usuario
        switch (event.key.code) {
            case sf::Keyboard::Up: nuevaPosicion.y -= speed*2; break; // Movimiento hacia arriba
            case sf::Keyboard::Down: nuevaPosicion.y += speed*2; break; // Movimiento hacia abajo
            case sf::Keyboard::Left: nuevaPosicion.x -= speed*2; break; // Movimiento hacia la izquierda
            case sf::Keyboard::Right: nuevaPosicion.x += speed*2; break; // Movimiento hacia la derecha
            default: break;
        }

        // Establece la nueva posición provisionalmente
        base.setPosition(nuevaPosicion);

        // Verifica si hay una colisión en la nueva posición
        if (!mapa.colision(base) && !mapa.colisionBloque(base)) {
            // Si no hay colisión, mueve al personaje
            //mover(event);
        } else {
            // Si hay una colisión, restablece a la posición anterior
            base.setPosition(posicionActual);
        }
    }

} 

void personaje::setSpritePosition()
{
    p1.setPosition(base.getPosition()+sf::Vector2f(0, -11.f));
}

std::vector<std::unique_ptr<explosion>>& personaje::getExplosion()
{
    return explo;
}


if (event.key.code == sf::Keyboard::Space && actualTime.asMilliseconds() > time.asMilliseconds() + 100)
        {
            time = clock.getElapsedTime();
            for (int i = 0; i < 2; i++)
            {
                if (p.getExplosion()[i]->getBombaState()==false)
                {
                    p.getExplosion()[i]->setTime(clock);
                    p.getExplosion()[i]->deleteBomba(clock, window, mapa, p.dibujarBase());
                    break;
                }
            }
            
            
        }

        for (int i = 0; i < 2; i++)
        {
            if(p.getExplosion()[i]->getBombaState())
            {
                p.getExplosion()[i]->colision(p.dibujarBase());
                p.getExplosion()[i]->deleteBomba(clock, window, mapa, p.dibujarBase());
            }
        }

        p.setSpritePosition();


