#include "personaje.h"

#include <iostream>
#include <string>

personaje::personaje()
{   
    texture.loadFromFile("imagenes/bomberman.png");
    p1.setTexture(texture);
    p1.setPosition(sf::Vector2f(40.f, 40.f));
    
    base.setSize(sf::Vector2f(24.f, 24.f));
    base.setPosition(sf::Vector2f(80, 80));

    for(int i=0; i<2; i++) explo.push_back(std::make_unique<explosion>());

    speed = 0.25f;
}

personaje::personaje(int val)
{
    if (val == 2)
    {
        up = sf::Keyboard::W;
        down = sf::Keyboard::S;
        left = sf::Keyboard::A;
        right = sf::Keyboard::D;
        putBomba = sf::Keyboard::Q;
        texture.loadFromFile("imagenes/bomberman_2.png");
        texture2.loadFromFile("imagenes/bomberman1_2.png");
        base.setPosition(sf::Vector2f(40*10, 40*14));
    }
    else
    {
        up = sf::Keyboard::Up;
        down = sf::Keyboard::Down;
        left = sf::Keyboard::Left;
        right = sf::Keyboard::Right;
        putBomba = sf::Keyboard::Space;
        texture.loadFromFile("imagenes/bomberman.png");
        texture2.loadFromFile("imagenes/bomberman1.png");
        base.setPosition(sf::Vector2f(80, 80));
    }
    
    //life = 3;

    p1.setTexture(texture);
    //p1.setPosition(sf::Vector2f(40.f, 40.f));
    
    base.setSize(sf::Vector2f(24.f, 24.f));
    //base.setPosition(sf::Vector2f(80, 80));

    for(int i=0; i<2; i++) explo.push_back(std::make_unique<explosion>());

    speed = 0.25f;

    colision_ = false;
}

sf::Sprite& personaje::dibujar()
{
    return p1;
}

sf::RectangleShape& personaje::dibujarBase()
{
    return base;
}

void personaje::setSpeed(float speed_)
{
    speed = speed_;
}

void personaje::setPosicion()
{
    p1.setPosition(base.getPosition());
}

void personaje::setBasePosicion(sf::Vector2f position)
{
    base.setPosition(position);
}

void personaje::setColisionState()
{
    colision_ = true;
}

bool personaje::getColisionState()
{
    return colision_;
}

sf::Vector2f personaje::getPosicion()
{
    return base.getPosition();
}



void personaje::colisionPosition(sf::Event event, std::shared_ptr<mapaBloques> mapa)
{
    if (event.type == sf::Event::KeyPressed)
    {
        sf::Vector2f posicionActual = base.getPosition();
        sf::Vector2f nuevaPosicion = posicionActual;

        // Determina la nueva posición basada en la entrada del usuario
        
        if (event.key.code==up) nuevaPosicion.y -= speed*2; // Movimiento hacia arriba
        if (event.key.code==down) nuevaPosicion.y += speed*2; // Movimiento hacia abajo
        if (event.key.code==left) nuevaPosicion.x -= speed*2; // Movimiento hacia izquierda
        if (event.key.code==right) nuevaPosicion.x += speed*2; // Movimiento hacia derecha
        
        // Establece la nueva posición provisionalmente
        base.setPosition(nuevaPosicion);
        
        // Verifica si hay una colisión en la nueva posición
        if (!mapa->colision(base) && !mapa->colisionBloque(base)) {
            // Si no hay colisión, mueve al personaje
            //mover(event);
            //texture.loadFromFile("imagenes/bomberman1.png");
            p1.setTexture(texture2);
        } else {
            // Si hay una colisión, restablece a la posición anterior
            base.setPosition(posicionActual);
            //texture.loadFromFile("imagenes/bomberman.png");
            p1.setTexture(texture);
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

void personaje::explosionSequence(sf::Event &event, sf::Clock &clock, sf::RenderWindow &window, std::shared_ptr<mapaBloques> mapa, std::shared_ptr<personaje> per2)
{   
    actualTime = clock.getElapsedTime();

    if (event.type == sf::Event::KeyPressed)
    {
        colisionPosition(event, mapa);

        //std::thread hilo(personaje::colisionPosition, std::ref(event), std::ref(mapa));
        //hilo.join();
        //std::thread hilo(&personaje::colisionPosition, &p, std::ref(event), std::ref(mapa));
    }

    if (event.key.code == putBomba && actualTime.asMilliseconds() > time.asMilliseconds() + 400)
    {
        time = clock.getElapsedTime();
        for (int i = 0; i < 2; i++)
        {
            if (getExplosion()[i]->getBombaState()==false)
            {
                getExplosion()[i]->setTime(clock);
                getExplosion()[i]->deleteBomba(clock, window, mapa, dibujarBase());
                break;
            }
        }
        
        
    }

    for (int i = 0; i < 2; i++)
    {
        if(getExplosion()[i]->getBombaState())
        {
            if(getExplosion()[i]->colision(dibujarBase())) 
            {
                setColisionState();
                
            }
            if(getExplosion()[i]->colision(per2->dibujarBase())) 
            {
                per2->setColisionState();
            }

            getExplosion()[i]->deleteBomba(clock, window, mapa, dibujarBase());
        }
    }

    setSpritePosition();
}


