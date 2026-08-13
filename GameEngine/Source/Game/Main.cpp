#include "Engine.h"
#include "SpaceGame.h"
#include "Assets.h"

#include <fmod.hpp>
#include <map>
#include <memory>
#include <random>
#include <fstream>

#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"

using namespace sr;

int main()
{

    Factory::Instance().Register<Actor>("Actor");
    Factory::Instance().Register<Object>("Object");
    Factory::Instance().Register<Player>("Player");
    Factory::Instance().Register<Enemy>("Enemy");
    Factory::Instance().Register<Bullet>("Bullet");



    //Factory::Instance().Register<Actor>("Actor");
    //auto actor = Factory::Instance().Create<Actor>("Actor");

    //Factory::Instance().Register<Object>("Object");
    //auto object = Factory::Instance().Create<Object>("Object");

    //std::cout << actor->IsActive() << std::endl;
    //std::cout << object->IsActive() << std::endl;

    //json::document_t document;
    //if (json::Load("Assets/Data/stupid.json", document)) {
    //    actor->Read(document);
    //    std::cout << actor->GetName() << std::endl;
    //    std::cout << actor->GetTag() << std::endl;
    //}
    //else {
    //    return -525600;
    //}

    //std::cout << actor->GetTransform().rot << std::endl;
  

    //return 0;

    //INITIALIZE
    Engine::Get().Initialize();
    
    SpaceGame game;
    game.Initialize();

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

            Engine::Get().GetRenderer().Present();
        }
        //SHUTDOWN
    Engine::Get().Shutdown();

        return 0;


    }

