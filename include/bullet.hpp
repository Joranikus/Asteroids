
#ifndef ASTEROIDS_BULLET_HPP
#define ASTEROIDS_BULLET_HPP

#include "movement_handler.hpp"
#include "threepp/threepp.hpp"

using namespace threepp;

class Bullet : public MovementHandler {

public:

    Bullet(const std::shared_ptr<Sprite>& bullet_sprite, Vector2 direction, float initial_velocity)
        : MovementHandler(bullet_sprite, direction, initial_velocity, 0, 0, 0) {}

    std::shared_ptr<Sprite> get_sprite() {
        return object_;
    }

    void update(float dt) override {
        MovementHandler::update(dt);
    }

};

#endif//ASTEROIDS_BULLET_HPP