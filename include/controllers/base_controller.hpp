
#ifndef ASTEROIDS_BASE_CONTROLLER_HPP
#define ASTEROIDS_BASE_CONTROLLER_HPP

#include "threepp/threepp.hpp"
#include <cmath>

using namespace threepp;

class BaseController {

public:
    BaseController(const std::shared_ptr<Sprite>& sprite,
                   Vector2 direction,
                   float rotation_speed = 0.0f,
                   float friction_coefficient = 0.0f,
                   float thrust_power = 0.0f,
                   float initial_velocity = 0.0f,
                   float initial_rotation_velocity = 0.0f)

        : sprite_(sprite),
          direction_(direction),
          rotation_speed_(rotation_speed),
          friction_coefficient_(friction_coefficient),
          thrust_power_(thrust_power),
          velocity_float_(initial_velocity),
          initial_rotation_velocity_(initial_rotation_velocity) {

        velocity_.x = direction_.x * velocity_float_;
        velocity_.y = direction_.y * velocity_float_;

    }

    virtual void set_mark_for_removal() {
        marked_for_removal = true;
    }

    virtual void update(float dt) {
        velocity_.x -= friction_coefficient_ * velocity_.x * dt;
        velocity_.y -= friction_coefficient_ * velocity_.y * dt;

        sprite_->position.x += velocity_.x * dt;
        sprite_->position.y += velocity_.y * dt;

        sprite_->material->rotation += initial_rotation_velocity_ * dt;
    }

    //Rotates material
    virtual void rotate_counter_clockwise(float dt) {
        auto material = sprite_->material;
        if (material) {
            update_direction();
            material->rotation += rotation_speed_ * dt;
        }
    }

    virtual void rotate_clockwise(float dt) {
        auto material = sprite_->material;
        if (material) {
            update_direction();
            material->rotation -= rotation_speed_ * dt;
        }
    }

    // thrust is a scalar that is multiplied into the direction vector
    virtual void thrust_forward(float dt) {
        update_direction();
        velocity_.x += direction_.x * thrust_power_ * dt;
        velocity_.y += direction_.y * thrust_power_ * dt;
    }

    virtual void thrust_backward(float dt) {
        update_direction();
        velocity_.x -= direction_.x * thrust_power_ * dt;
        velocity_.y -= direction_.y * thrust_power_ * dt;
    }

    virtual Vector2 get_position() {
        return {sprite_->position.x, sprite_->position.y};
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

    virtual void set_position(Vector2 position) {
        sprite_->position.x = position.x;
        sprite_->position.y = position.y;
    }

    virtual void set_velocity(const Vector2& velocity) {
        velocity_ = velocity;
    }

    virtual void set_direction(const Vector2& direction) {
        direction_ = direction;
    }

    virtual void set_rotation_speed(float& rotation_speed) {
        rotation_speed_ = rotation_speed;
    }

    std::shared_ptr<Sprite> sprite_;
    bool marked_for_removal = false;

private:

    virtual void update_direction() {
        auto material = sprite_->material;
        if (material) {
            float theta = material->rotation + (2 * atanf(1)); // (atanf(1) * 4) = pi
            direction_.x = cosf(theta);
            direction_.y = sinf(theta);
        }
    }

    Vector2 direction_;
    float rotation_speed_;
    float friction_coefficient_;
    float thrust_power_;
    float velocity_float_;
    float initial_rotation_velocity_;

    Vector2 velocity_;

};

#endif//ASTEROIDS_BASE_CONTROLLER_HPP