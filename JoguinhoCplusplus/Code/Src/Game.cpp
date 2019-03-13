#include "../Include/Game.h"
#include "../Include/Map.h"
#include "../Include/Collision.h"
#include "../Include/EntityComponentSystem/components.h"

#include <time.h>

SDL_Renderer *Game::renderer_ = nullptr;
SDL_Event Game::event_;

void Game::run() {
    srand(static_cast<unsigned int>(time(NULL)));
    const int fps = 60;
    const int frameDelay = 1000 / fps;

    while (this->isRunning()) {
        Uint32 frameStart = SDL_GetTicks();

        this->handleEvents();
        this->update();
        this->render();

        int frameTime = SDL_GetTicks() - frameStart;
        if (frameDelay > frameTime) {
            SDL_Delay(frameDelay - frameTime);
        }
    }
    this->clean();
}

void Game::init(const std::string &title, const int &xpos, const int &ypos,
                const int &width, const int &height, const bool &fullscreen) {
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
        std::cout << "SDL_INIT_EVERYTHING foi bem sucedido\n";
        this->window_ = SDL_CreateWindow(title.c_str(), xpos, ypos, width,
                                         height,
                                         fullscreen ? SDL_WINDOW_FULLSCREEN : SDL_WINDOW_SHOWN);
        if (this->window_) {
            std::cout << "janela criada\n";
        }
        Game::renderer_ = SDL_CreateRenderer(this->window_, -1, 0);
        if (Game::renderer_) {
            SDL_SetRenderDrawColor(Game::renderer_, 0xFF, 0xFF, 0xFF, 0xFF);
            std::cout << "renderer criado\n";
        }

        this->is_running_ = true;
    } else {
        this->is_running_ = false;
        return;
    }

    this->manager_ = new GameManager();
    auto player_info = this->game_properties_["player_1_info"];
    // auto map_info = this->game_properties_["map_info"];

    // this->game_objects_.map_ = new Map(Game::renderer_, this->manager_);
    // this->game_objects_.map_->loadMap(map_info["lvl_0"]["source"],
    //                     map_info["lvl_0"]["sizes"]["x"],
    //                     map_info["lvl_0"]["sizes"]["y"]);
    // this->game_objects_.map_->pushDirtIntoColliders(&this->colliders_);

    this->game_objects_.player_ = this->manager_->addEntity();
    this->game_objects_.player_->addGroup(kplayer_group);
    this->game_objects_.player_->addComponent<Transform>().setScale(player_info["in_game_scale"]);
    this->game_objects_.player_->addComponent<Sprite>(Game::renderer_,
                                                      player_info["sprite_sheet_info"]["source"],
                                                      player_info["sprite_sheet_info"]["idle"]["frames"],
                                                      player_info["sprite_sheet_info"]["idle"]["speed"],
                                                      player_info["sprite_sheet_info"]["animated"]);
    this->game_objects_.player_->addComponent<Input>(&Game::event_);
    this->game_objects_.player_->addComponent<PlayerBorder>(Game::renderer_,
                                                            player_info["collider_info"]["source"],
                                                            player_info["in_game_scale"],
                                                            player_info["collider_info"]["animation_info"]["frames"],
                                                            player_info["collider_info"]["animation_info"]["speed"],
                                                            player_info["collider_info"]["animated"]);
    this->game_objects_.player_->addComponent<BoxCollider>(player_info["tag"]).getPushedOn(&this->colliders_);
    this->game_objects_.player_->getComponent<BoxCollider>()
        ->setColliderDimension(player_info["collider_info"]["dimensions"]["width"],
                               player_info["collider_info"]["dimensions"]["height"],
                               player_info["in_game_scale"]);

    this->game_objects_.wall_ = this->manager_->addEntity();
    this->game_objects_.wall_->addGroup(kmap_group);
    this->game_objects_.wall_->addComponent<Transform>(Vector2D(300.0f, 300.0f), 1, 32, 32);
    this->game_objects_.wall_->addComponent<Sprite>(Game::renderer_, "Assets/dirt.png");
    this->game_objects_.wall_->addComponent<BlockBorder>(Game::renderer_, "Assets/borda_bloco.png");
    this->game_objects_.wall_->addComponent<BoxCollider>("wall");
    this->game_objects_.wall_->getComponent<BoxCollider>()
        ->setColliderBasedOnBorder(this->game_objects_.wall_->getComponent<BlockBorder>())
        .getPushedOn(&this->colliders_);
}

void Game::update() {
    auto player_pos = this->game_objects_.player_->getComponent<Transform>()->getPosition();

    this->manager_->refresh();
    this->manager_->update();

    auto player_collider = this->game_objects_.player_->getComponent<BoxCollider>();
    for (auto &collider : this->colliders_) {
        if (collider->getTag() != this->game_properties_["player_1_info"]["tag"] &&
            Collision::AABB(player_collider, collider)) {
            this->game_objects_.player_->getComponent<Transform>()->setPosition(player_pos);
        }
    }
}

void Game::render() {
    auto &tiles(this->manager_->getGroup(kmap_group));
    auto &players(this->manager_->getGroup(kplayer_group));
    auto &enemies(this->manager_->getGroup(kenemy_group));

    SDL_RenderClear(Game::renderer_);

    for (auto &tile : tiles) {
        tile->draw();
    }
    for (auto &player : players) {
        player->draw();
    }
    for (auto &enemy : enemies) {
        enemy->draw();
    }

    SDL_RenderPresent(Game::renderer_);
}

void Game::handleEvents() {
    SDL_PollEvent(&Game::event_);
    switch (Game::event_.type) {
    case SDL_QUIT:
        this->is_running_ = false;
    default:
        break;
    }
}

void Game::clean() {
    SDL_DestroyWindow(this->window_);
    SDL_DestroyRenderer(Game::renderer_);
    delete this->manager_;
    SDL_Quit();

    std::cout << "o jogo foi limpado\n";
}