#include "../Include/Game.h"
#include "../Include/Map.h"
#include "../Include/Collision.h"
#include "../Include/EntityComponentSystem/components.h"

#include <time.h>

SDL_Renderer* Game::renderer_ = nullptr;
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

void Game::init(const std::string& title, const int& xpos, const int& ypos,
                const int& width, const int& height, const bool& fullscreen) {
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

    this->map_ = new Map(Game::renderer_, this->manager_);
    this->map_->loadMap("Assets/lvl_0.map", 16, 16);
	this->map_->pushDirtIntoColliders(&this->colliders_);

    this->player_ = this->manager_->addEntity();
    this->player_->addGroup(kplayer_group);
    this->player_->addComponent<Transform>();
    this->player_->getComponent<Transform>()->setScale(2);
    this->player_->addComponent<Sprite>(Game::renderer_, "Assets/cool_player.png",
                                        8, 150, true);
    this->player_->addComponent<Input>(&Game::event_);
	this->player_->addComponent<PlayerBorder>(Game::renderer_,
                                              "Assets/borda_unica_cool_player.png",
											  this->player_->getComponent<Transform>()->getScale());
    this->player_->addComponent<BoxCollider>("player");
	this->player_->getComponent<BoxCollider>()
        ->setColliderBasedOnBorder(this->player_->getComponent<PlayerBorder>())
                                    .getPushedOn(&this->colliders_);

    // this->wall_ = this->manager_->addEntity();
    // this->wall_->addGroup(kmap_group);
    // this->wall_->addComponent<Transform>(Vector2D(300.0f, 300.0f), 1, 32, 32);
    // this->wall_->addComponent<Sprite>(Game::renderer_, "Assets/dirt.png");
	// this->wall_->addComponent<BlockBorder>(Game::renderer_, "Assets/borda_bloco.png");
    // this->wall_->addComponent<BoxCollider>("wall").getPushedOn(&this->colliders_);
}

void Game::update() {
    auto player_pos = this->player_->getComponent<Transform>()->getPosition();

    this->manager_->refresh();
    this->manager_->update();

	// std::cout << player_pos;

	auto player_collider = this->player_->getComponent<BoxCollider>();
    for (auto& collider : this->colliders_) {
        if (collider->getTag() != "player" &&
			Collision::AABB(player_collider, collider)) {
            this->player_->getComponent<Transform>()->setPosition(player_pos);
        }
    }
}

void Game::render() {
    auto& tiles(this->manager_->getGroup(kmap_group));
    auto& players(this->manager_->getGroup(kplayer_group));
    auto& enemies(this->manager_->getGroup(kenemy_group));
    
    SDL_RenderClear(Game::renderer_);
    
    for (auto& tile : tiles) {
        tile->draw();
    }
    for (auto& player : players) {
        player->draw();
    }
    for (auto& enemy : enemies) {
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