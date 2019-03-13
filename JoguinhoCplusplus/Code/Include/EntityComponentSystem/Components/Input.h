#pragma once

#include "SDL2/SDL.h"

#include "../ECS.h"

class Input : public Component {
  private:
    SDL_Event *event_;

    Vector2D velocity_ = Vector2D();

    float speed_ = 2.0f;

  public:
    Input() = default;

    Input(SDL_Event *event) {
        this->setEvent(event);
    }

    ~Input() {
        std::cout << "destrutor do Input_component Chamado\n";
    }

    void init() override {
        return;
    }

    void update() override {
        if (this->event_->type == SDL_KEYDOWN) {
            switch (this->event_->key.keysym.sym) {
            case SDLK_w:
                this->velocity_.setY(-1.0f);
                break;
            case SDLK_a:
                this->velocity_.setX(-1.0f);
                break;
            case SDLK_s:
                this->velocity_.setY(1.0f);
                break;
            case SDLK_d:
                this->velocity_.setX(1.0f);
                break;
            default:
                break;
            }
        }

        if (this->event_->type == SDL_KEYUP) {
            switch (this->event_->key.keysym.sym) {
            case SDLK_w:
                this->velocity_.setY(0.0f);
                break;
            case SDLK_a:
                this->velocity_.setX(0.0f);
                break;
            case SDLK_s:
                this->velocity_.setY(0.0f);
                break;
            case SDLK_d:
                this->velocity_.setX(0.0f);
                break;
            default:
                break;
            }
        }
    }

    void draw() override {
        return;
    }

    void setEvent(SDL_Event *event) {
        this->event_ = event;
    }

    float getSpeed() {
        return this->speed_;
    }

    Vector2D &getVelocity() {
        return this->velocity_;
    }
};