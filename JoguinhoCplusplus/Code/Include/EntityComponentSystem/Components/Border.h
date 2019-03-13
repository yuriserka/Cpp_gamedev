#pragma once

#include "../ECS.h"
#include "Sprite.h"

class Border : public Component {
  protected:
	Sprite *border_img_ = nullptr;
	Transform *transform_ = nullptr;

  public:
	void init() override {
		return;
	}

	virtual void update() = 0;

	void draw() override {
		this->border_img_->draw();
	}

	Transform *getTransform() {
		return this->transform_;
	}

	virtual ~Border() = default;
};

class PlayerBorder : public Border {
  public:
	PlayerBorder() = default;

	PlayerBorder(SDL_Renderer *renderer, const std::string &imgPath, const int &scale = 1) {
		this->border_img_ = new Sprite(renderer, imgPath);
		this->border_img_->init();
		this->transform_ = this->border_img_->getTransform();
		this->transform_->setScale(scale);
	}

	PlayerBorder(SDL_Renderer *renderer, const std::string &imgPath,
				 const int &scale, const int &frames, const int &speed,
				 const bool &animated) {
		this->border_img_ = new Sprite(renderer, imgPath, frames, speed, animated);
		this->border_img_->init();
		this->transform_ = this->border_img_->getTransform();
		this->transform_->setScale(scale);
	}

	~PlayerBorder() {
		std::cout << "destrutor do Border_component Chamado\n";
		delete this->border_img_;
	}

	void update() override {
		if (this->entity_) {
			auto entity_position = this->entity_->getComponent<Transform>()->getPosition();
			this->transform_->setPosition(entity_position);
		}
		this->border_img_->update();
	}
};

class BlockBorder : public Border {
  public:
	BlockBorder() = default;

	BlockBorder(SDL_Renderer *renderer, const std::string &imgPath, const int &scale = 1) {
		this->border_img_ = new Sprite(renderer, imgPath);
		this->border_img_->init();
		this->transform_ = this->border_img_->getTransform();
		this->transform_->setScale(scale);
	}

	~BlockBorder() {
		std::cout << "destrutor do Border_component Chamado\n";
		delete this->border_img_;
	}

	void update() override {
		if (this->entity_) {
			auto entity_position = this->entity_->getComponent<Transform>()->getPosition();
			this->transform_->setPosition(entity_position);
		}
		this->border_img_->update();
	}
};