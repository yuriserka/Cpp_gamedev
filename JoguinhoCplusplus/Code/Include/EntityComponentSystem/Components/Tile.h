#pragma once

#include "SDL2/SDL.h"

#include "../ECS.h"
#include "Transform.h"
#include "Sprite.h"
#include "Border.h"

class Tile : public Component {

private:
    SDL_Rect tileRect_;
    SDL_Renderer* renderer_;

    int id_;
    std::string img_path_;

    Transform* transform_ = nullptr;
    Sprite* sprite_ = nullptr;
	BlockBorder* border = nullptr;

	enum {
		kdirt,
		kwater,
		kgrass
	}tile_types;
public:
    Tile(SDL_Renderer* renderer, const int& id) {
        this->renderer_ = renderer;
        this->id_ = id;

        switch (this->id_) {
        case kdirt:
            this->img_path_ = "Assets/dirt.png";
            break;
        case kwater:
            this->img_path_ = "Assets/water.png";
            break;
        case kgrass:
           this->img_path_ = "Assets/grass.png";
            break;
        default:
			this->img_path_ = "Assets/tile_test.png";
            break;
        }
    }

    Tile(SDL_Renderer* renderer, const int& xpos, const int& ypos,
         const int& id, const int& width = 32,
         const int& height = 32) : Tile(renderer, id) {
        this->setTileRect(xpos, ypos, width, height);
    }

    ~Tile() {
        std::cout << "destrutor do Tile_component Chamado\n";
        if (!this->entity_) {
            delete transform_;
            delete sprite_;
			delete border;
        }
    }

    void init() override {
        if (this->entity_) {
            if (!this->entity_->hasComponent<Transform>()) {
                this->entity_->addComponent<Transform>(static_cast<float>(this->tileRect_.x),
                                                       static_cast<float>(this->tileRect_.y),
                                                       1, this->tileRect_.h, this->tileRect_.w);
            }
            if (!this->entity_->hasComponent<Sprite>()) {
                this->entity_->addComponent<Sprite>(this->renderer_,
                                                    this->img_path_);
            }

            this->sprite_ = this->entity_->getComponent<Sprite>();
            this->transform_ = this->entity_->getComponent<Transform>();
		}
		else {
			if (!this->sprite_) {
				this->sprite_ = new Sprite(this->renderer_, this->img_path_);
			}
			if (!this->transform_) {
				this->transform_ = new Transform(static_cast<float>(this->tileRect_.x),
												 static_cast<float>(this->tileRect_.y),
												 1, this->tileRect_.h, this->tileRect_.w);
			}
		}

		if (this->id_ == kdirt) {
			this->entity_->addComponent<BlockBorder>(this->renderer_, "Assets/tile_test.png");
			this->border = this->entity_->getComponent<BlockBorder>();
		}

		if (this->border) {
			this->border->getTransform()->setPosition(this->transform_->getPosition());
		}
    }

    void update() override {
		return;
    }

    void draw() override {
        this->sprite_->draw();
    }

    void setTileRect(const int& x, const int& y, const int& w = 32,
                     const int& h = 32) {
        this->tileRect_.x = x;
        this->tileRect_.y = y;
        this->tileRect_.w = w;
        this->tileRect_.h = h;
    }

    int getId() const {
        return this->id_;
    }

};