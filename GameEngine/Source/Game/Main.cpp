#include "Engine.h"
#include "SpaceGame.h"
#include "Assets.h"

#include <fmod.hpp>
#include <map>
#include <memory>
#include <random>
#include <fstream>

using namespace sr;

int main()
{
    // load the json data from a file
    std::string buffer;
    if (ReadTextFile("Assets/Data/data.json", buffer))
    {
        // show the contents of the json file (debug)
        std::cout << buffer << std::endl;

        // create json document from the json file contents
        rapidjson::Document document;
        if (json::Load("Assets/Data/data.json", document))
        {
            // read/show the data from the json file
            int age;
            std::string name;
            float speed;
            bool isAwake;
            Vector2 position;
            Vector3 color;

            // read the json data
            JSON_READ(document, name);
            JSON_READ(document, age);
            JSON_READ(document, speed);
            JSON_READ(document, isAwake);
            JSON_READ(document, position);
            JSON_READ(document, color);

            // show the data
            std::cout << name << " " << age << " " << speed << " " << isAwake << std::endl;
            std::cout << position.x << " " << position.y << std::endl;
            std::cout << color.r << " " << color.g << " " << color.b << " " << std::endl;
        }
    }

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

