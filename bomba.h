#ifndef BOMBA_
#define BOMBA_

#include <SFML/Graphics.hpp>

class bomba
{
    private:
    sf::Texture texture;
    sf::Sprite bombita_;
    sf::RectangleShape bomba_;
    sf::RectangleShape *explosion;
    sf::Time time;
    sf::Time actualTime;

    int bombSize = 2;

    public:
    bomba();
    bomba(sf::Vector2f, sf::Clock);
    ~bomba();
    sf::RectangleShape dibujarBomba();
    sf::Sprite dibujarBombita();

    sf::RectangleShape* dibujarExplosion();
    void setPosition(sf::Vector2f);
    void explosionBomba(sf::Clock);
    bool colision(sf::RectangleShape, int []);
    
};

#endif