
#ifndef ASTEROIDS_SPACESHIP_PHYSICS_HPP
#define ASTEROIDS_SPACESHIP_PHYSICS_HPP

#include "spaceship_class.hpp"
#include "threepp/threepp.hpp"
#include <iostream>

class SpaceshipPhysics {

public:

    SpaceshipPhysics(SpaceshipClass& spaceship, float rotation_speed)
        : spaceship_(spaceship),
          rotation_speed_(rotation_speed) {}

    void perform_spaceship_movement(SpaceshipController::Action action, float dt) {
        switch (action) {
            case SpaceshipController::Action::RotateLeft:
                rotate_counter_clockwise(dt);
                break;
            case SpaceshipController::Action::RotateRight:
                rotate_clockwise(dt);
                break;
            case SpaceshipController::Action::ThrustForward:
                thrust_forward(dt);
                break;
            case SpaceshipController::Action::ThrustBackward:
                thrust_backward(dt);
                break;
            default:
                break;
        }
    }

private:

    float rotation_speed_;
    SpaceshipClass& spaceship_;

    void rotate_counter_clockwise(float dt) {
        auto material = std::dynamic_pointer_cast<SpriteMaterial>(spaceship_.material);
        if (material) {
            material->rotation += rotation_speed_ * dt;
        }
    }

    void rotate_clockwise(float dt) {
        auto material = std::dynamic_pointer_cast<SpriteMaterial>(spaceship_.material);
        if (material) {
            material->rotation -= rotation_speed_ * dt;
        }
    }

    void thrust_forward(float dt) {
        spaceship_.position.x += 1 * dt;
        std::cout << spaceship_.position.x << std::endl;
    }

    void thrust_backward(float dt) {
        spaceship_.position.x -= 1 * dt;
        std::cout << spaceship_.position.x << std::endl;
    }

};

#endif//ASTEROIDS_SPACESHIP_PHYSICS_HPP
