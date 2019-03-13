#pragma once

#include "SDL2/SDL.h"

#include "../ECS.h"
#include "Transform.h"
#include "Sprite.h"
#include "Border.h"

class BoxCollider : public Component {
  private:
    SDL_Rect collider_;
    std::string tag_;

  public:
    BoxCollider() = default;

    BoxCollider(const std::string &tag) {
        this->tag_ = tag;
    }

    ~BoxCollider() {
        std::cout << "destrutor do BoxCollider_component Chamado\n";
    }

    void init() override {
        if (this->entity_) {
            if (!this->entity_->hasComponent<Transform>()) {
                this->entity_->addComponent<Transform>();
            }
        }
        
        auto entity_transform = this->entity_->getComponent<Transform>();
        this->setColliderDimension(entity_transform->getwidth(),
                                   entity_transform->getHeight(),
                                   entity_transform->getScale());
    }

    void update() override {
        auto entity_position = this->entity_->getComponent<Transform>()->getPosition();
        this->collider_.x = static_cast<int>(entity_position.getX());
        this->collider_.y = static_cast<int>(entity_position.getY());
    }

    void draw() override {
        return;
    }

    void getPushedOn(std::vector<BoxCollider *> *colliders) {
        colliders->push_back(this);
    }

    BoxCollider &setColliderDimension(const int &w, const int &h, const int &scale = 1) {
        this->collider_.w = w * scale;
        this->collider_.h = h * scale;

        return *this;
    }

    BoxCollider &setColliderBasedOnBorder(Border *border) {
        auto border_transform = border->getTransform();
        this->collider_.w = border_transform->getwidth() * border_transform->getScale();
        this->collider_.h = border_transform->getHeight() * border_transform->getScale();

        return *this;
    }

    SDL_Rect getCollider() const {
        return this->collider_;
    }

    std::string getTag() const {
        return this->tag_;
    }
};