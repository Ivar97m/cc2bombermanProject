#ifndef _BLOQUE_
#define _BLOQUE_

#include <SFML/Graphics.hpp>

#include "bloqueBase.h"

class bloque : public bloqueBase
{       
    public:
        bloque();
        void setTexture();

};

bloque::bloque()
{
    setTexture();
}

void bloque::setTexture()
{
    texture.loadFromFile("imagenes/bloque(1).png");
}

#endif