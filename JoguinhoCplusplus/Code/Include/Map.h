#pragma once

#include <iostream>
#include <vector>

#include "SDL2/SDL.h"

#include "EntityComponentSystem/Components/Sprite.h"
#include "EntityComponentSystem/Components/Tile.h"
#include "EntityComponentSystem/Components/BoxCollider.h"
#include "EntityComponentSystem/ECS.h"

class Map {
private:
    SDL_Renderer* renderer_ = nullptr;

    GameManager* manager_ = nullptr;
public:
    Map() = default;

    Map(SDL_Renderer* renderer, GameManager* manager) {
        this->setRenderer(renderer);
        this->setManager(manager);
    }

    ~Map() {
        std::cout << "destrutor do Map Chamado\n";
    }

    void addTile(const int& xpos, const int& ypos, const int& id,
                      const int& height = 32, const int& width = 32) {
        auto tile = this->manager_->addEntity();
        
        tile->addComponent<Tile>(this->renderer_, xpos, ypos, id, width, height);
        tile->addGroup(kmap_group);
    }

	void pushDirtIntoColliders(std::vector<BoxCollider*>* colliders) {
		for (auto entity : this->manager_->getGroup(kmap_group)) {
			auto tile = entity->hasComponent<Tile>() ? entity->getComponent<Tile>() : nullptr;
			if (tile) {
				if (tile->getId() == 0) {
					tile->entity_->addComponent<BoxCollider>("dirt_tile").setColliderDimension(32, 32).getPushedOn(colliders);
				}
			}
		}
	}

    void loadMap(std::string path, int size_x, int size_y);

    void setRenderer(SDL_Renderer* renderer) {
        this->renderer_ = renderer;
    }

    void setManager(GameManager* manager) {
        this->manager_ = manager;
    }
};