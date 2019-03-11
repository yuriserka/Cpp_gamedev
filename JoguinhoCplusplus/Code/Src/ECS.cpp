#include "../Include/EntityComponentSystem/ECS.h"

void Entity::addGroup(const Group& group) {
    this->groupBitSet_[group] = true;
    this->manager_->addToGroup(this, group);
}