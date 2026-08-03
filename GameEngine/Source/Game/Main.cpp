#include "Engine.h"
#include "Player.h"
#include "Enemy.h"
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

    Engine::Get().GetAudio().AddSound("bass", "Assets/Sounds/bass.wav");
    Engine::Get().GetAudio().AddSound("clap", "Assets/Sounds/clap.wav");
    Engine::Get().GetAudio().AddSound("close-hat", "Assets/Sounds/close-hat.wav");
    Engine::Get().GetAudio().AddSound("cowbell", "Assets/Sounds/cowbell.wav");
    Engine::Get().GetAudio().AddSound("open-hat", "Assets/Sounds/open-hat.wav");
    Engine::Get().GetAudio().AddSound("snare", "Assets/Sounds/snare.wav");


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

        if (Engine::Get().GetInput().GetKeyPressed(SDL_SCANCODE_1)) { Engine::Get().GetAudio().PlaySound("bass"); }
        if (Engine::Get().GetInput().GetKeyPressed(SDL_SCANCODE_2)) { Engine::Get().GetAudio().PlaySound("clap"); }
        if (Engine::Get().GetInput().GetKeyPressed(SDL_SCANCODE_3)) { Engine::Get().GetAudio().PlaySound("close-hat"); }
        if (Engine::Get().GetInput().GetKeyPressed(SDL_SCANCODE_4)) { Engine::Get().GetAudio().PlaySound("cowbell"); }
        if (Engine::Get().GetInput().GetKeyPressed(SDL_SCANCODE_5)) { Engine::Get().GetAudio().PlaySound("open-hat"); }
        if (Engine::Get().GetInput().GetKeyPressed(SDL_SCANCODE_6)) { Engine::Get().GetAudio().PlaySound("snare"); }

        Engine::Get().Update();

        float dt = Engine::Get().GetTime().GetDeltaTime();

        game.Update(dt, Engine::Get().GetScreen().x, Engine::Get().GetScreen().y);
            
        //RENDER
            Engine::Get().GetRenderer().SetColor(0.0f, 0.0f, 0.0f);
            Engine::Get().GetRenderer().Clear();

            Engine::Get().GetRenderer().SetColor(1.0f, 1.0f, 1.0f);
            
            game.Draw(Engine::Get().GetRenderer());

            Engine::Get().GetPS().Draw(Engine::Get().GetRenderer());

            Engine::Get().GetRenderer().Present();
        }
        //SHUTDOWN
    Engine::Get().Shutdown();

        return 0;


    }

