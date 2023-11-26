
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

        // used for initial velocity so that the object moves when created
        velocity_.x = direction_.x * velocity_float_;
        velocity_.y = direction_.y * velocity_float_;

        // these check if the class is initiated correctly with correct values
        if (!sprite) {
            throw std::runtime_error("Sprite not found");
        }

        if (!sprite->material) {
            throw std::runtime_error("Sprite material not found");
        }

        if (std::abs(direction.length() - 1.0f) > 0.001) { // because direction vector always has a length of 1
            throw std::invalid_argument("Direction vector must be normalized");
        }

        if (friction_coefficient < 0.0f || friction_coefficient > 1.0f) { // 0 = no friction, 1 = all the friction
            throw std::invalid_argument("Friction coefficient must be between 0 and 1.");
        }

        if (thrust_power < 0) { // an engine can't have negative horsepower
            throw std::invalid_argument("Thrust power must be positive");
        }
    }

    virtual void update(const float dt) {
        velocity_.x -= friction_coefficient_ * velocity_.x * dt;
        velocity_.y -= friction_coefficient_ * velocity_.y * dt;

        sprite_->position.x += velocity_.x * dt;
        sprite_->position.y += velocity_.y * dt;

        sprite_->material->rotation += initial_rotation_velocity_ * dt;
    }

    virtual void rotate_counter_clockwise(const float dt) {
        update_direction();
        sprite_->material->rotation += rotation_speed_ * dt;
    }

    virtual void rotate_clockwise(const float dt) {
        update_direction();
        sprite_->material->rotation -= rotation_speed_ * dt;
    }

    // thrust is a scalar that is multiplied into the direction vector
    virtual void thrust_forward(const float dt) {
        update_direction();
        velocity_.x += direction_.x * thrust_power_ * dt;
        velocity_.y += direction_.y * thrust_power_ * dt;
    }

    virtual void thrust_backward(const float dt) {
        update_direction();
        velocity_.x -= direction_.x * thrust_power_ * dt;
        velocity_.y -= direction_.y * thrust_power_ * dt;
    }

    // getters
    virtual Vector2 get_position() const {
        return {sprite_->position.x, sprite_->position.y};
    }

    virtual Vector2 get_velocity() const {
        return velocity_;
    }

    virtual Vector2 get_direction() const {
        return direction_;
    }

    virtual float get_rotation_speed() const {
        return rotation_speed_;
    }

    // setters
    virtual void set_position(const Vector2 position) {
        sprite_->position.x = position.x;
        sprite_->position.y = position.y;
    }

    virtual void set_velocity(const Vector2& velocity) {
        velocity_ = velocity;
    }

    virtual void set_direction(const Vector2& direction) {
        if (std::abs(direction.length() - 1.0f) > 0.001) {
            throw std::invalid_argument("Direction vector must be normalized");
        }

        direction_ = direction;
    }

    virtual void set_rotation_speed(const float rotation_speed) {
        rotation_speed_ = rotation_speed;
    }

    std::shared_ptr<Sprite> sprite_;
    bool marked_for_removal = false;

private:
    void update_direction() {
        float theta = sprite_->material->rotation + (2 * atanf(1));// (atanf(1) * 4) = pi
        direction_.x = cosf(theta);
        direction_.y = sinf(theta);
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