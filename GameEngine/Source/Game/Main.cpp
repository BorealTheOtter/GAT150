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
    {
        //read input file
        std::ifstream file("Assets/Data/txt.txt");
        if (file.is_open())
        {
            std::string str;
            while (std::getline(file, str)) {
                std::cout << str << std::endl;
            }
            
        }
        else {
            std::cerr << "dumbass spelt the file wrong";
        }
        file.close();
    }

    {
        //write output file
        std::ofstream file("Assets/Data/txt.txt", std::ios::app);
        if (file.is_open()) {
            file << "have a good day.\n";
        }
    }

    {
        //read/write
        std::fstream file("Assets/Data/txt.txt",std::ios::in | std::ios::out | std::ios::app);
        if (file.is_open()) {
            file << "add a line.\n";
            file.seekg(0);
            std::string str;
            while (std::getline(file, str)) {
                std::cout << str << std::endl;
            }

        }
    }

    {
        std::string name;
        int score;
        bool isAlive;

        bool save = false;
        if (save) 
        {
            name = "Boreal";
            score = 525600;
            isAlive = true;

            //save game data
            std::ofstream file("Assets/Data/game.txt", std::ios::trunc);
            if (file.is_open()) {
                file << name << "\n" << score << "\n" << isAlive;
            }

        }
        bool load = true;
        if (load) {
            //load game data
            std::ifstream file("Assets/Data/game.txt");
            if (file.is_open()) {
                std::getline(file, name);
                std::string str;
                file >> str;
                score = std::stoi(str);
                file >> isAlive;
            }
        }
        //display game data
        std::cout << name << std::endl;
        std::cout << score << std::endl;
        std::cout << isAlive << std::endl;
    }

    return 0;

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

