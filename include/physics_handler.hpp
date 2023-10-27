
#ifndef ASTEROIDS_PHYSICS_HANDLER_HPP
#define ASTEROIDS_PHYSICS_HANDLER_HPP

#include "threepp/threepp.hpp"
#include <iostream>

using namespace threepp;

class PhysicsEngine {

public:

    PhysicsEngine(Sprite& sprite, Vector2 direction, Vector2 velocity, float rotation_speed, float thrust_power)
            : sprite_(sprite),
              velocity_(velocity),
              direction_(direction),
              rotation_speed_(rotation_speed),
              thrust_power_(thrust_power) {}

    virtual void update(float dt) {
        sprite_.position.x += velocity_.x * dt;
        sprite_.position.y += velocity_.y * dt;
    }

    virtual void rotate_counter_clockwise(float dt) {
        auto material = std::dynamic_pointer_cast<SpriteMaterial>(sprite_.material);
        if (material) {
            material->rotation += rotation_speed_ * dt;
        }
    }

    virtual void rotate_clockwise(float dt) {
        auto material = std::dynamic_pointer_cast<SpriteMaterial>(sprite_.material);
        if (material) {
            material->rotation -= rotation_speed_ * dt;
        }
    }

    virtual void thrust_forward(float dt) {
        velocity_.x += direction_.x * thrust_power_ * dt;
        velocity_.y += direction_.y * thrust_power_ * dt;
        std::cout << sprite_.position << std::endl;
    }

    virtual void thrust_backward(float dt) {
        velocity_.x -= direction_.x * thrust_power_ * dt;
        velocity_.y -= direction_.y * thrust_power_ * dt;
        std::cout << sprite_.position << std::endl;
    }

    virtual Vector2 get_velocity() {
        return velocity_;
    }

    virtual Vector2 get_direction() {
        return direction_;
    }

    virtual float get_rotation_speed() {
        return rotation_speed_;
    }

    virtual void set_velocity(Vector2& velocity) {
        velocity_ = velocity;
    }

    virtual void set_direction(Vector2& direction) {
        direction_ = direction;
    }

    virtual void set_rotation_speed(float& rotation_speed) {
        rotation_speed_ = rotation_speed;
    }

private:

    Sprite& sprite_;
    Vector2 direction_;
    Vector2 velocity_;
    float rotation_speed_;
    float thrust_power_;

};

#endif//ASTEROIDS_PHYSICS_HANDLER_HPP
