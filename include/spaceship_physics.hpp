
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
                //thrust_forward(dt);
                break;
            case SpaceshipController::Action::ThrustBackward:
                //thrust_backward(dt);
                break;
            default:
                break;
        }
    }

private:

    float rotation_speed_;
    SpaceshipClass& spaceship_;
    Vector2 velocity = Vector2(0, 0);
    Vector2 direction = Vector2(0, -1);

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

    //void thrust_forward(float amount) {
      //  velocity += direction * amount;
    //}

    //void thrust_backward(float amount) {
      //  velocity -= direction * amount;
    //}


   // void update_position(float dt) {
     //   spaceship_.position.x += velocity.x * dt;
     //   spaceship_.position.y += velocity.y * dt;
    //}

};

#endif//ASTEROIDS_SPACESHIP_PHYSICS_HPP