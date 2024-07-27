#ifndef EXPLOSION_
#define EXPLOSION_

#include <SFML/Graphics.hpp>

#include "bomba.h"
#include "mapaBloques.h"

#include <memory>

class explosion
{

    bomba *bom;
    sf::Time time;
    sf::Time actualTime;

    bool bombaState;
    int bombDisplay[10] = {0}; //cuidado
    sf::RectangleShape *arrExplosion = nullptr;


    public:
    explosion();
    void setTime(sf::Clock);
    bool getBombaState();
    void deleteBomba(sf::Clock, sf::RenderWindow &, std::shared_ptr<mapaBloques>, sf::RectangleShape &);
    bool colision(sf::RectangleShape &);

};

#endif