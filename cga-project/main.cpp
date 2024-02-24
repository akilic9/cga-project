#include <SFML/Graphics.hpp>
#include "Game.h"

int main()
{
    Game game;
    game.Init();
    sf::Clock clock;
    
    //TODO: asMiliseconds uses int32? Maybe switch to seconds?
    float elapsedTime = clock.restart().asMilliseconds();

    const float& fixedFrameTime = 1.f / 60.f;

    //Game loop
    while (game.GetWindow().IsOpen())
    {
        float deltaTime = clock.restart().asMilliseconds();
        game.HandleInput();
        game.Update(deltaTime);

        elapsedTime += deltaTime;
        if (elapsedTime >= fixedFrameTime) {
            game.FixedUpdate();
            elapsedTime -= fixedFrameTime;
        }

        game.FixedUpdate();
        game.Render();
    }

    return 0;
}