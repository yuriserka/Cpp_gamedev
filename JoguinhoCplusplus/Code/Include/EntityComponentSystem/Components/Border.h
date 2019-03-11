#pragma once

#include "../ECS.h"
#include "Sprite.h"

class Border : public Component {
protected:
	Sprite* border_img = nullptr;
	Transform* transform = nullptr;
public:
	void init() override {
		return;
	}

	virtual void update() = 0;

	void draw() override {
		this->border_img->draw();
	}

	Transform* getTransform() {
		return this->transform;
	}

	virtual ~Border() = default;
};

class PlayerBorder : public Border {
public:
	PlayerBorder() = default;

	PlayerBorder(SDL_Renderer* renderer, const std::string& imgPath, const int& scale = 1) {
		this->border_img = new Sprite(renderer, imgPath, true);
		this->border_img->init();
		this->transform = this->border_img->getTransform();
		this->transform->setScale(scale);
	}

	PlayerBorder(SDL_Renderer* renderer, const std::string& imgPath,
				const int& scale, const int& frames, const int& speed,
           		const bool& animated) {
		this->border_img = new Sprite(renderer, imgPath, frames, speed, animated);
		this->border_img->init();
		this->transform = this->border_img->getTransform();
		this->transform->setScale(scale);
	}

	~PlayerBorder() {
		std::cout << "destrutor do Border_component Chamado\n";
		delete this->border_img;
	}

	void update() override {
		if (this->entity_) {
			auto entity_position = this->entity_->getComponent<Transform>()->getPosition();
			this->transform->setPosition(entity_position);
		}
		this->border_img->update();
	}
};

class BlockBorder : public Border {
public:
	BlockBorder() = default;

	BlockBorder(SDL_Renderer* renderer, const std::string& imgPath, const int& scale = 1) {
		this->border_img = new Sprite(renderer, imgPath, true);
		this->border_img->init();
		this->transform = this->border_img->getTransform();
		this->transform->setScale(scale);
	}

	~BlockBorder() {
		std::cout << "destrutor do Border_component Chamado\n";
		delete this->border_img;
	}

	void update() override {
		if (this->entity_) {
			auto entity_position = this->entity_->getComponent<Transform>()->getPosition();
			this->transform->setPosition(entity_position);
		}
		this->border_img->update();
	}
};