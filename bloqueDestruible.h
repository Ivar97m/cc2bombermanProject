#ifndef _BLOQUE_DESTRUIBLE
#define _BLOQUE_DESTRUIBLE

#include "bloqueBase.h"

class bloqueDestruible: public bloqueBase
{
    public:
    bloqueDestruible();
    void setTexture();
};

bloqueDestruible::bloqueDestruible()
{
    setTexture();
}

void bloqueDestruible::setTexture()
{
    texture.loadFromFile("imagenes/bloqueDestruible.png");
}

#endif