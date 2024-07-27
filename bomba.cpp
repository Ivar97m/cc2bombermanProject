#include "bomba.h"
#include <iostream>

bomba::bomba()
{
    bomba_.setSize(sf::Vector2f(10.f, 10.f));
    bomba_.setPosition(sf::Vector2f(100.f, 100.f));
    bomba_.setFillColor(sf::Color::Red);
    
}

bomba::bomba(sf::Vector2f position, sf::Clock clock)
{
    bomba_.setSize(sf::Vector2f(10.f, 10.f));
    bomba_.setPosition(position);
    bomba_.setFillColor(sf::Color::Red);
    time = clock.getElapsedTime();
    explosion = nullptr;

    texture.loadFromFile("imagenes/bomba.png");
    bombita_.setTexture(texture);
    bombita_.setPosition(position);
}

bomba::~bomba()
{
    //delete bomba_;
    delete explosion;
    explosion = nullptr;
}

sf::RectangleShape bomba::dibujarBomba()
{
    return bomba_;
}

sf::Sprite bomba::dibujarBombita()
{
    return bombita_;
}

sf::RectangleShape* bomba::dibujarExplosion()
{
    return explosion;
}

void bomba::setPosition(sf::Vector2f position)
{
    bomba_.setPosition(position);
}

void bomba::explosionBomba(sf::Clock clock)
{   
    actualTime = clock.getElapsedTime();

    if(actualTime.asMilliseconds() >= time.asMilliseconds() + 2e3)
    {
        if (explosion == nullptr)
        {
            explosion = new sf::RectangleShape[bombSize*5];
            for (int i = 0; i < bombSize; i++)
            {   
                for (int j = 0; j < 5; j++)
                {
                    float size = 40.f;
                    if (j == 0)
                    {   
                        explosion[i*5 + j].setSize(sf::Vector2f(size, size));
                        explosion[i*5 + j].setFillColor(sf::Color::Yellow);
                        explosion[i*5 + j].setPosition(bomba_.getPosition() + sf::Vector2f(0, 0));

                    }
                    else if (j == 1)
                    {
                        explosion[i*5 + j].setSize(sf::Vector2f(size, size));
                        explosion[i*5 + j].setFillColor(sf::Color::Yellow);
                        explosion[i*5 + j].setPosition(bomba_.getPosition() + sf::Vector2f(size*(i+1), 0));
                    }
                    else if (j == 2)
                    {
                        explosion[i*5 + j].setSize(sf::Vector2f(size, size));
                        explosion[i*5 + j].setFillColor(sf::Color::Yellow);
                        explosion[i*5 + j].setPosition(bomba_.getPosition() + sf::Vector2f(-size*(i+1), 0));
                    }
                    else if (j == 3)
                    {
                        explosion[i*5 + j].setSize(sf::Vector2f(size, size));
                        explosion[i*5 + j].setFillColor(sf::Color::Yellow);
                        explosion[i*5 + j].setPosition(bomba_.getPosition() + sf::Vector2f(0, size*(i+1)));
                    }
                    else if (j == 4)
                    {
                        explosion[i*5 + j].setSize(sf::Vector2f(size, size));
                        explosion[i*5 + j].setFillColor(sf::Color::Yellow);
                        explosion[i*5 + j].setPosition(bomba_.getPosition() + sf::Vector2f(0, -size*(i+1)));
                    }
                }

            }
            
        }
    }
}

bool bomba::colision(sf::RectangleShape sprite, int arr[])
{
    if (explosion!=nullptr)
    {
        for (int i = 0; i < bombSize*5; i++)
        {   
            if ((explosion[i]).getGlobalBounds().intersects(sprite.getGlobalBounds()) && arr[i]==1)
            {
                return true;
            }
        }
    }
    
    return false;
}
