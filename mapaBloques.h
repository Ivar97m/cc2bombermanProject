#ifndef _MAPA_BLOQUES_
#define _MAPA_BLOQUES_

#include "bloque.h"
#include "bloqueDestruible.h"
#include "baseVerde.h"

#include <cmath>
#include <memory>

#include <SFML/Graphics.hpp>

class mapaBloques
{
    bloque *bloques = new bloque[165];
    bloqueDestruible *bloqueDestruible_ = new bloqueDestruible[165];
    baseVerde *sueloVerde = new baseVerde[165];

    private:
        int vec[11][15]=   {{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                            {1, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                            {1, 2, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1},
                            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                            {1, 2, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1},
                            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                            {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1},
                            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                            {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 2, 1},
                            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 1},
                            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};

        sf::Vector2f mapa_[11][15];
        sf::Vector2f mapa_bloquesDestruibles[11][15];
        sf::Vector2f mapa_baseVerde[11][15];

        sf::Texture bomberface1_;
        sf::Sprite bomberface1;

        sf::Texture bomberface2_;
        sf::Sprite bomberface2;

        sf::Texture heart_;
        sf::Sprite heart;

        sf::Texture heart_2;
        sf::Sprite heart2;

        //sf::Text text1;
        //sf::Font font;

    public:
        mapaBloques();
        ~mapaBloques();
        void dibujarMapa(sf::RenderWindow &);
        bool colision(sf::RectangleShape);
        bool colisionBloque(sf::RectangleShape);

        void setPosition(sf::RectangleShape, sf::RenderWindow &);
};

#endif