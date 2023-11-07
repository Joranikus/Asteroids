
#ifndef ASTEROIDS_BULLET_HPP
#define ASTEROIDS_BULLET_HPP

#include "movement_handler.hpp"
#include "threepp/threepp.hpp"

using namespace threepp;

class Bullet : public MovementHandler {

public:

    Bullet(Sprite& bullet_sprite, Vector2 direction, float initial_velocity)
        : MovementHandler(bullet_sprite, direction, initial_velocity, 0, 0, 0) {}

    Sprite& get_sprite() {
        return sprite_;
    }

    void update(float dt) override {
        MovementHandler::update(dt);
    }

};

#endif//ASTEROIDS_BULLET_HPP
