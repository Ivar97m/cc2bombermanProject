#ifndef _BOMBERMAN_
#define _BOMBERMAN_

#include <SFML/Graphics.hpp>
#include "bomba.h"
#include "mapaBloques.h"
#include "explosion.h"
#include "personaje.h"


#include <cmath>
#include <memory>
#include <vector>
#include <thread>

class personaje
{
    private:
        sf::Vector2f posicion;
        sf::Texture texture;
        sf::Texture texture2;
        sf::Sprite p1;
        sf::RectangleShape base;

        std::vector<std::unique_ptr<explosion>> explo;

        sf::Time time;
        sf::Time actualTime;

        sf::Keyboard::Key up;
        sf::Keyboard::Key down;
        sf::Keyboard::Key left;
        sf::Keyboard::Key right;
        sf::Keyboard::Key putBomba;

        float speed;

        bool colision_;

        //int life;

    public:
        personaje();
        personaje(int);
        sf::Sprite& dibujar();
        sf::RectangleShape& dibujarBase();
        void setSpeed(float speed);
        void setPosicion();
        void setBasePosicion(sf::Vector2f);
        void setSpritePosition();

        sf::Vector2f getPosicion();
        void setColisionState();
        bool getColisionState();

        void colisionPosition(sf::Event, std::shared_ptr<mapaBloques>);

        std::vector<std::unique_ptr<explosion>>& getExplosion();

        void explosionSequence(sf::Event &, sf::Clock &, sf::RenderWindow &, std::shared_ptr<mapaBloques>, std::shared_ptr<personaje>);

};

#endif


