#ifndef _BASEVERDE_
#define _BASEVERDE_

#include "bloqueBase.h"

class baseVerde: public bloqueBase
{
    public:
    baseVerde();
    void setTexture();

};

baseVerde::baseVerde()
{
    setTexture();
}

void baseVerde::setTexture()
{
    texture.loadFromFile("imagenes/baseVerde.png");
}

#endif