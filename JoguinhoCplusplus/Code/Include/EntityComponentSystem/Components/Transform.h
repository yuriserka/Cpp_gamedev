#pragma once

#include "../ECS.h"
#include "../../Vector2D.h"

#include "Input.h"

class Transform : public Component {

private:
    Vector2D position_ = Vector2D();

    SDL_Rect src_;
    SDL_Rect dest_;
    
    int height_ = 32;
    int width_ = 32;
    int scale_ = 1;
public:
    Transform() = default;

    Transform(const float& x, const float& y) {
        this->setPosition(x, y);
    }

	Transform(const Vector2D& position) {
		this->setPosition(position);
	}

    Transform(const float& x, const float& y, const int& scale, const int& height,
              const int& width) : Transform(x, y) {
        this->setHeight(height);
        this->setWidth(width);
        this->setScale(scale);
    }

	Transform(const Vector2D& position, const int& scale, const int& height,
		const int& width) : Transform(position) {
		this->setHeight(height);
		this->setWidth(width);
		this->setScale(scale);
	}

    ~Transform() {
        std::cout << "destrutor do Transform_component Chamado\n";
    }

    void init() override {
        return;
    }

    void update() override {
        if (this->entity_) {
            if (this->entity_->hasComponent<Input>()) {
                auto entity_velocity = this->entity_->getComponent<Input>()->getVelocity();
                auto entity_speed = this->entity_->getComponent<Input>()->getSpeed();
                
                float tmpXpos = this->position_.getX() + (entity_velocity.getX() *
                                                  entity_speed);
                float tmpYpos = this->position_.getY() + (entity_velocity.getY() *
                                                        entity_speed);
                this->position_.setX(tmpXpos);
                this->position_.setY(tmpYpos);
            }
        }
        float tmpXpos = this->position_.getX();
        float tmpYpos = this->position_.getY();

        this->position_.setX(tmpXpos);
        this->position_.setY(tmpYpos);
    }

    void draw() override {
        return;
    }

    void setPosition(const float& x, const float& y) {
        this->position_.setX(x);
        this->position_.setY(y);
    }

    void setPosition(const Vector2D& position) {
        this->position_ = position;
    }

    Vector2D& getPosition() {
        return this->position_;
    }

    void setDimensions(const int& width, const int& height) {
        this->setWidth(width);
        this->setHeight(height);
    }

    void setScale(const int& scale) {
        this->scale_ = scale;
    }

    int getScale() const {
        return this->scale_;
    }

    void setHeight(const int& height) {
        this->height_ = height;
    }

    int getHeight() const {
        return this->height_;
    }

    void setWidth(const int& width) {
        this->width_ = width;
    }

    int getwidth() const {
        return this->width_;
    }

    void setDestRect(int w, int h, int x = 0, int y = 0) {
        this->dest_.w = w;
        this->dest_.h = h;
        this->dest_.x = x;
        this->dest_.y = y;
    }

    SDL_Rect* getDestRect() {
        return &this->dest_;
    }

    void setSrcRect(int w, int h, int x = 0, int y = 0) {
        this->src_.w = w;
        this->src_.h = h;
        this->src_.x = x;
        this->src_.y = y;
    }

    SDL_Rect* getSrcRect() {
        return &this->src_;
    }

};