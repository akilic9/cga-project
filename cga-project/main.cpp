#include <SFML/Graphics.hpp>
#include "Game.h"

int main()
{
    Game game;
    game.Init();
    sf::Clock clock;
    
    float elapsedTime = clock.restart().asSeconds();

    const float& fixedFrameTime = 1.f / 60.f;

    //Game loop
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