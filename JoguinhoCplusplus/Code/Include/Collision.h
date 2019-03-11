#pragma once

#include "SDL2/SDL.h"

class BoxCollider;

class Collision {

public:
    Collision() = default;
    ~Collision() = default;

    static const bool AABB(const SDL_Rect& rect_a, const SDL_Rect& rect_b);
    static const bool AABB(const BoxCollider& collider_a, const BoxCollider& collider_b);
    static const bool AABB(const BoxCollider* collider_a, const BoxCollider* collider_b);

};