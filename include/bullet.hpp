
#ifndef ASTEROIDS_BULLET_HPP
#define ASTEROIDS_BULLET_HPP

#include "physics_handler.hpp"
#include "threepp/threepp.hpp"

using namespace threepp;

class Bullet : public PhysicsEngine {

public:

    Bullet(Sprite& bulletSprite, Vector2 direction, float initial_velocity)
        : PhysicsEngine(bulletSprite, direction, initial_velocity, 0, 0, 0) {}

    Sprite& get_sprite() {
        return sprite_;
    }

    void update(float dt) override {
        PhysicsEngine::update(dt);
    }

};

#endif//ASTEROIDS_BULLET_HPP
