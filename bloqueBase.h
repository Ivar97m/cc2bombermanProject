#ifndef _BLOQUE_BASE_
#define _BLOQUE_BASE_

#include <SFML/Graphics.hpp>

class bloqueBase
{   
    protected:
        sf::Texture texture;
        sf::Sprite cuadrado;
    
    public:
        bloqueBase();

        //METODO PLANTILLA
        void plantilla()
        {
            setTexture();
            setPosition(sf::Vector2f(80.f, 80.f));
            getPosition();
            getBounds();
            dibujar();
        }

        virtual void setTexture() = 0;
        
        void setPosition(sf::Vector2f);
        sf::Sprite dibujar();
        sf::Vector2f getPosition();
        sf::FloatRect getBounds();

};

#endif