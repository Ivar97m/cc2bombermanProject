#include "bloqueBase.h"

bloqueBase::bloqueBase()
{
    texture.loadFromFile("imagenes/bloque(1).png");
    cuadrado.setTexture(texture);
    cuadrado.setPosition(100.f, 100.f);
}

sf::Vector2f bloqueBase::getPosition()
{
    return cuadrado.getPosition();
}

sf::FloatRect bloqueBase::getBounds()
{
    return cuadrado.getGlobalBounds();
}

void bloqueBase::setPosition(sf::Vector2f v)
{
    cuadrado.setPosition(v);
}

sf::Sprite bloqueBase::dibujar()
{
    return cuadrado;
}