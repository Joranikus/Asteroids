
#ifndef ASTEROIDS_SPACESHIP_PHYSICS_HPP
#define ASTEROIDS_SPACESHIP_PHYSICS_HPP

#include "physics_handler.hpp"
#include "spaceship_class.hpp"
#include "threepp/threepp.hpp"
#include <iostream>

class SpaceshipPhysics : public PhysicsEngine {

public:
    SpaceshipPhysics(SpaceshipClass& spaceship, float rotation_speed, float thrust_power)
        : PhysicsEngine(spaceship, Vector2(0, 1), Vector2(0, 0), rotation_speed, thrust_power) {}

    //controls the actual spaceship
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