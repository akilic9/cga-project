#include <SFML/Graphics.hpp>
#include "Game.h"

/******************************************************************************************************************
    This project's code heavily uses the book SFML Game Development By Example by Raimondas Pupius as source. 
    Reference: Pupius, R. (2015) SFML Game Development By Example. Birmingham: Packt Publishing Ltd.
******************************************************************************************************************/

int main()
{
    srand(time(0));

    Game game;
    game.Init();
    sf::Clock clock;
    
    float elapsedTime = clock.restart().asSeconds();

    const float& fixedFrameTime = 1.f / 60.f;

    //Game loop https://gafferongames.com/post/fix_your_timestep/
    while (game.GetWindow().IsOpen())
    {
        float deltaTime = clock.restart().asSeconds();
        game.HandleInput();
        game.Update(deltaTime);

        elapsedTime += deltaTime;
        if (elapsedTime >= fixedFrameTime) {
            game.FixedUpdate();
            elapsedTime -= fixedFrameTime;
        }

        game.FixedUpdate();
        game.Render();
        game.LateUpdate();
    }

    return 0;
}