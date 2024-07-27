#include "configuration.h"

configuration::configuration(sf::Clock clock)
{
    portada_.loadFromFile("imagenes/portada.png");
    portada.setTexture(portada_);

    text1.setString("START");
    text1.setFont(font);
    text1.setCharacterSize(50);
    text1.setFillColor(sf::Color::White);

    text2.setString("-->");
    text2.setFont(font);
    text2.setCharacterSize(50);
    text2.setFillColor(sf::Color::White);
    
    font.loadFromFile("imagenes/font.ttf");
    time = clock.getElapsedTime();
    
    flecha = -1;
    state = -1;

    life1 = 3;
    life2 = 3;

    vida1.setFont(font);
    vida1.setCharacterSize(40);
    vida1.setFillColor(sf::Color::White);
    vida1.setPosition(sf::Vector2f(605.f, 195.f));

    vida2.setFont(font);
    vida2.setCharacterSize(40);
    vida2.setFillColor(sf::Color::White);
    vida2.setPosition(sf::Vector2f(605.f, 495.f));

    winner_.setFont(font);
    winner_.setCharacterSize(40);
    winner_.setFillColor(sf::Color::White);
    winner_.setPosition(sf::Vector2f(100.f, 300.f));

    bomberface1_.loadFromFile("imagenes/bomberface2.png");
    bomberface1.setTexture(bomberface1_);
    bomberface1.setPosition(sf::Vector2f(450.f, 290.f));

    bomberface2_.loadFromFile("imagenes/bomberface.png");
    bomberface2.setTexture(bomberface2_);
    bomberface2.setPosition(sf::Vector2f(450.f, 290.f));

}

void configuration::inicio(sf::RenderWindow &window, sf::Event &event, sf::Time &actualTime)
{
    portada.setPosition(sf::Vector2f(20.f, 10.f));

    text1.setPosition(sf::Vector2f(180.f, 360.f));

    text2.setPosition(sf::Vector2f(60.f, 360.f + 60.f*flecha));

    if (actualTime.asMilliseconds() > time.asMilliseconds() + 400)
    {       
        
        if (event.type == sf::Event::EventType::KeyPressed)
        {
            std::cout << "entraaa" << std::endl;
            if (event.key.code == sf::Keyboard::Down)
            {   
                if(flecha < 1)
                flecha++;
            }

            else if (event.key.code == sf::Keyboard::Up)
            {
                if(flecha > -1)
                flecha--;
            }

            if (event.key.code == sf::Keyboard::Right)
            {
                state = flecha;
                std::cout << "entra a juego>>" << std::endl;
            }
            
            std::cout << flecha << "  " << state<< std::endl;
            std::cout << event.key.code << std::endl;
            time = actualTime;
            
        }
    }

    window.draw(portada);
    window.draw(text1);
    window.draw(text2);
    
}

void configuration::juego()
{

}

int configuration::getState()
{
    return state;
}

int configuration::getLessLife()
{
    if(life1<life2) return life1;
    else return life2;
}

void configuration::winner(sf::RenderWindow &window)
{
    winner_.setString("El ganador es...");
    window.draw(winner_);

    if (life1>life2) window.draw(bomberface1);
    else window.draw(bomberface2);
    
    
}

void configuration::setState(int estado)
{
    state = estado;
}

void configuration::resetLives()
{
    life1 = 3;
    life2 = 3;
}

void configuration::drawLife(sf::RenderWindow &window)
{
    vida1.setString(std::to_string(life1));
    window.draw(vida1);

    vida2.setString(std::to_string(life2));
    window.draw(vida2);
}

void configuration::reduceVida1()
{
    life1--;
}

void configuration::reduceVida2()
{
    life2--;
}

