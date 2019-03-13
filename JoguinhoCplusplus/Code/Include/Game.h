#pragma once

#include "SDL2/SDL.h"

#include <vector>
#include <array>
#include <iostream>
#include <fstream>

#include "./Json/json.hpp"

using json = nlohmann::json;

class BoxCollider;
class GameManager;
class Entity;
class Map;

class Game {
  private:
    bool is_running_ = false;
    SDL_Window *window_ = nullptr;

    GameManager *manager_ = nullptr;
    std::vector<BoxCollider *> colliders_;

    struct GameObjects {
        Entity *player_ = nullptr;
        Entity *wall_ = nullptr;
        Map *map_ = nullptr;
    } game_objects_;

    json game_properties_;

    void openGameProperties() {
        std::fstream json_file("Properties/game_properties.json");
        if (!json_file.is_open()) {
            std::cout << "fail to opem game properties\n";
            return;
        }

        json game_configs;
        json_file >> this->game_properties_;
    }

  public:
    Game() = default;

    Game(const std::string &title, const int &xpos, const int &ypos,
         const int &width, const int &height, const bool &fullscreen) {
        this->openGameProperties();
        this->init(title, xpos, ypos, width, height, fullscreen);
    }

    ~Game() = default;

    static SDL_Renderer *renderer_;
    static SDL_Event event_;

    void run();

    bool isRunning() const {
        return this->is_running_;
    }

    void init(const std::string &title, const int &xpos, const int &ypos,
              const int &width, const int &height, const bool &fullscreen);
    void handleEvents();
    void update();
    void render();
    void clean();
};