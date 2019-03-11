#include "../Include/Collision.h"
#include "../Include/EntityComponentSystem/Components/BoxCollider.h"

const bool Collision::AABB(const SDL_Rect& rect_a, const SDL_Rect& rect_b) {
    return SDL_HasIntersection(&rect_a, &rect_b);
}

const bool Collision::AABB(const BoxCollider& collider_a, const BoxCollider& collider_b) {
    if (Collision::AABB(collider_a.getCollider(), collider_b.getCollider())) {
        std::cout << collider_a.getTag() << " hit: " << collider_b.getTag() << "\n";
        return true;
    }
    
    return false;
}

const bool Collision::AABB(const BoxCollider* collider_a, const BoxCollider* collider_b) {
    if (Collision::AABB(collider_a->getCollider(), collider_b->getCollider())) {
        std::cout << collider_a->getTag() << " hit: " << collider_b->getTag() << "\n";
        return true;
    }

    return false;
}