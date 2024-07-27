#include "mapaBloques.h"

#include <iostream>

mapaBloques::mapaBloques()
{   
    float size = 40;
    for (int i = 0; i < 11; i++)
    {
        for (int j = 0; j < 15; j++)
        {
            if (vec[i][j]==1)
            {
                mapa_[i][j] = sf::Vector2f((i+1)*size, size*(j+1));
            }
            else mapa_[i][j] = sf::Vector2f(-2*size, -2*size);

            if(vec[i][j]==0)
            {
                mapa_bloquesDestruibles[i][j] = sf::Vector2f((i+1)*size, size*(j+1));
            }
            else mapa_bloquesDestruibles[i][j] = sf::Vector2f(-2*size, -2*size);

            mapa_baseVerde[i][j] = sf::Vector2f((i+1)*size, size*(j+1));

            std::cout << mapa_bloquesDestruibles[i][j].x << " " << mapa_bloquesDestruibles[i][j].y << "   ";
        }
        std::cout << std::endl;
    }

    for (int i = 0; i < 11; i++)
    {
         for (int j = 0; j < 15; j++)
         {
            (sueloVerde + 15*i + j)->setPosition(mapa_baseVerde[i][j]);
            (bloques + 15*i + j)->setPosition(mapa_[i][j]);
            (bloqueDestruible_ + 15*i + j)->setPosition(mapa_bloquesDestruibles[i][j]);
         }
         
    }

    bomberface1_.loadFromFile("imagenes/bomberface2.png");
    bomberface1.setTexture(bomberface1_);
    bomberface1.setPosition(sf::Vector2f(540.f, 100.f));

    bomberface2_.loadFromFile("imagenes/bomberface.png");
    bomberface2.setTexture(bomberface2_);
    bomberface2.setPosition(sf::Vector2f(540.f, 400.f));

    heart_.loadFromFile("imagenes/heart.png");
    heart.setTexture(heart_);
    heart.setPosition(sf::Vector2f(540.f, 200.f));

    heart_2.loadFromFile("imagenes/heart.png");
    heart2.setTexture(heart_2);
    heart2.setPosition(sf::Vector2f(540.f, 500.f));

    /*
    font.loadFromFile("imagenes/font.ttf");
    text1.setFont(font);
    text1.setCharacterSize(40);
    text1.setFillColor(sf::Color::White);
    text1.setPosition(sf::Vector2f(560.f, 300.f));
    */
    
}

mapaBloques::~mapaBloques()
{
    delete[] bloques;
    delete[] bloqueDestruible_;
    delete[] sueloVerde;
}

void mapaBloques::setPosition(sf::RectangleShape arrExplosion, sf::RenderWindow &window)
{
    int x = floor(arrExplosion.getPosition().x / 40.f);
    int y = floor(arrExplosion.getPosition().y / 40.f);
    std::cout << x << " " << y << " ";
    (bloqueDestruible_ + 15*(x-1) + y - 1)->setPosition(sf::Vector2f(-40.f, -40.f));
    //window.draw((bloqueDestruible_ + 15*(x-1) + y - 1)->dibujar());
}

void mapaBloques::dibujarMapa(sf::RenderWindow& rw)
{
    for (int i = 0; i < 165; i++)
    {
        rw.draw((sueloVerde+i)->dibujar());
        rw.draw((bloques+i)->dibujar());
        rw.draw((bloqueDestruible_+i)->dibujar());
    }
    
    rw.draw(bomberface1);
    rw.draw(heart);

    rw.draw(bomberface2);
    rw.draw(heart2);
    //text1.setString(std::to_string(life));
    //rw.draw(text1);

    
}

bool mapaBloques::colision(sf::RectangleShape sprite)
{   
    for (int i = 0; i < 165; i++)
    {   
        if ((bloques+i)->getBounds().intersects(sprite.getGlobalBounds()))
        {
            return true;
        }
    }
    
    return false;
}

bool mapaBloques::colisionBloque(sf::RectangleShape sprite)
{   
    for (int i = 0; i < 165; i++)
    {   
        if ((bloqueDestruible_+i)->getBounds().intersects(sprite.getGlobalBounds()))
        {
            return true;
        }
    }
    
    return false;
}
