
#ifndef ASTEROIDS_ASTEROID_CONTROLLER_HPP
#define ASTEROIDS_ASTEROID_CONTROLLER_HPP

#include "physics_controller.hpp"
#include "threepp/threepp.hpp"

using namespace threepp;

class AsteroidController: public PhysicsController {

public:

    AsteroidController(const std::shared_ptr<Sprite>& bullet_sprite, Vector2 direction, float initial_velocity)
        : PhysicsController(bullet_sprite, direction, initial_velocity, 0, 0, 0) {}

    std::shared_ptr<Sprite> get_sprite() override {
        return PhysicsController::get_sprite();
    }

    void update(float dt) override {
        PhysicsController::update(dt);
    }

};

#endif//ASTEROIDS_ASTEROID_CONTROLLER_HPP
