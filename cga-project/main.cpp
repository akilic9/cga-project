#include <SFML/Graphics.hpp>
//https://www.sfml-dev.org/tutorials/2.6/start-vc.php

int main()
{
    sf::RenderWindow window(sf::VideoMode(1600, 900), "CGA Project");

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::Black);
        window.display();
    }

    return 0;
}