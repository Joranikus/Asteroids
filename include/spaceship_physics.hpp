
#ifndef ASTEROIDS_SPACESHIP_PHYSICS_HPP
#define ASTEROIDS_SPACESHIP_PHYSICS_HPP

#include "physics_handler.hpp"
#include "spaceship_class.hpp"
#include "spaceship_keylistener.hpp"
#include "threepp/threepp.hpp"
#include <iostream>

using namespace threepp;

class SpaceshipPhysics : public PhysicsEngine {

public:

    SpaceshipPhysics(SpaceshipClass& spaceship, float rotation_speed, float thrust_power, float friction_coefficient)
        : PhysicsEngine(spaceship, Vector2(0, 1), Vector2(0, 0), rotation_speed, thrust_power, friction_coefficient) {}

    //Checks each action in an actions set individually so you can press multiple buttons at the same time
    void perform_spaceship_movement(const std::set<SpaceshipController::Action>& actions, float dt) {
        for (const auto& action : actions) {
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
    }

    void update(float dt) override {
        PhysicsEngine::update(dt);
    }

private:

    void rotate_counter_clockwise(float dt) override {
        PhysicsEngine::rotate_counter_clockwise(dt);
    }

    void rotate_clockwise(float dt) override {
        PhysicsEngine::rotate_clockwise(dt);
    }

    void thrust_forward(float dt) override {
        PhysicsEngine::thrust_forward(dt);
    }

    void thrust_backward(float dt) override {
        PhysicsEngine::thrust_backward(dt);
    }

};

#endif//ASTEROIDS_SPACESHIP_PHYSICS_HPP