
#ifndef ASTEROIDS_BULLET_CONTROLLER_HPP
#define ASTEROIDS_BULLET_CONTROLLER_HPP

#include "object_controller.hpp"
#include "threepp/threepp.hpp"

using namespace threepp;

class BulletController: public PhysicsController {

public:
    BulletController(const std::shared_ptr<Sprite>& bullet_sprite, Vector2 direction, float initial_velocity)
        : PhysicsController(bullet_sprite, direction, initial_velocity, 0, 0, 0) {}

    std::shared_ptr<Sprite> get_sprite() override {
        return PhysicsController::get_sprite();
    }

    void update(float dt) override {
        PhysicsController::update(dt);
    }

};

#endif//ASTEROIDS_BULLET_CONTROLLER_HPP