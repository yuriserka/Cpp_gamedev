#pragma once

#include "SDL2/SDL.h"

#include <vector>
#include <array>
#include <iostream>

class BoxCollider;
class GameManager;
class Entity;
class Map;

class Game {

private:
    bool is_running_ = false;
    SDL_Window* window_ = nullptr;

    GameManager* manager_ = nullptr;
    Entity* player_ = nullptr;
    Entity* wall_ = nullptr;
    Map* map_ = nullptr;

	std::array<Entity*, 5> tiles;
    std::vector<BoxCollider*> colliders_;
public:
    Game() = default;

    Game(const std::string& title, const int& xpos, const int& ypos,
         const int& width, const int& height, const bool& fullscreen) {
        this->init(title, xpos, ypos, width, height, fullscreen);
    }

    ~Game() = default;

    static SDL_Renderer* renderer_;
    static SDL_Event event_;

    void run();

    bool isRunning() const {
        return this->is_running_;
    }

    void init(const std::string& title, const int& xpos, const int& ypos,
              const int& width, const int& height, const bool& fullscreen);
    void handleEvents();
    void update();
    void render();
    void clean();

};