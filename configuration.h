#ifndef _CONFIG_
#define _CONFIG_

#include <SFML/Graphics.hpp>
#include <iostream>

class configuration
{
    int state;
    sf::Texture portada_;
    sf::Sprite portada;
    sf::Text text1;
    sf::Text text2;
    sf::Font font;
    sf::Time time;

    int life1;
    int life2;

    sf::Text vida1;
    sf::Text vida2;

    sf::Text winner_;
    sf::Texture bomberface1_;
    sf::Sprite bomberface1;

    sf::Texture bomberface2_;
    sf::Sprite bomberface2;

    int flecha;
    
    configuration(sf::Clock);

    public:
        //configuration(sf::Clock);
        static configuration& getInstance(sf::Clock clock)
        {
            static configuration instance(clock);
            return instance;
        }
        configuration(const configuration&) = delete;
        configuration operator=(const configuration&) = delete;


        void inicio(sf::RenderWindow&, sf::Event &, sf::Time &);
        void juego();
        void winner(sf::RenderWindow &);

        int getState();
        void setState(int);
        int getLessLife();
        void resetLives();

        void reduceVida1();
        void reduceVida2();

        void drawLife(sf::RenderWindow &);
};

#endif