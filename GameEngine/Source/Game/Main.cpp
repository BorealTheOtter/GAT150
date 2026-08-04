#include "Engine.h"
#include "SpaceGame.h"
#include "Assets.h"

#include <fmod.hpp>
#include <map>
#include <memory>

using namespace sr;

int main()
{

    //INITIALIZE
    Engine::Get().Initialize();
    
    SpaceGame game;
    game.Initialize();

    // create texture, using shared_ptr so texture can be shared
    std::shared_ptr<Texture> texture = std::make_shared<Texture>();
    texture->Load("Assets/Images/testimg.jpg", Engine::Get().GetRenderer());

    //MAIN LOOP
    bool quit = false;
    while (!quit) {

        //UPDATE
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                quit = true;
            }
            if (Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_ESCAPE)) {
                quit = true;
            }
        }

        Engine::Get().Update();

        float dt = Engine::Get().GetTime().GetDeltaTime();

        game.Update(dt, Engine::Get().GetScreen().x, Engine::Get().GetScreen().y);
            
        //RENDER
            Engine::Get().GetRenderer().SetColor(0.0f, 0.0f, 0.0f);
            Engine::Get().GetRenderer().Clear();

            Engine::Get().GetRenderer().SetColor(1.0f, 1.0f, 1.0f);
            
            game.Draw(Engine::Get().GetRenderer());

            Engine::Get().GetPS().Draw(Engine::Get().GetRenderer());

            Engine::Get().GetRenderer().DrawTexture(texture.get(), 30, 30);

            Engine::Get().GetRenderer().Present();
        }
        //SHUTDOWN
    Engine::Get().Shutdown();

        return 0;


    }

