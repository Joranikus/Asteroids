
#ifndef ASTEROIDS_OBJECT_CONTROLLER_HPP
#define ASTEROIDS_OBJECT_CONTROLLER_HPP

#include "threepp/threepp.hpp"
#include <iostream>
#include <cmath>

using namespace threepp;

class ObjectController {

public:
    ObjectController(const std::shared_ptr<Sprite>& object, Vector2 direction,
                     float initial_velocity, float rotation_speed, float thrust_power, float friction_coefficient)
        : object_(object),
          velocity_float_(initial_velocity),
          direction_(direction),
          rotation_speed_(rotation_speed),
          thrust_power_(thrust_power),
          friction_coefficient_(friction_coefficient) {

        velocity_.x = direction_.x * velocity_float_;
        velocity_.y = direction_.y * velocity_float_;
    }

    virtual void update(float dt) {
        velocity_.x -= friction_coefficient_ * velocity_.x * dt;
        velocity_.y -= friction_coefficient_ * velocity_.y * dt;

        object_->position.x += velocity_.x * dt;
        object_->position.y += velocity_.y * dt;
    }

    //Rotates material
    virtual void rotate_counter_clockwise(float dt) {
        auto material = object_->material;
        if (material) {
            update_direction();
            material->rotation += rotation_speed_ * dt;
        }
    }

    virtual void rotate_clockwise(float dt) {
        auto material = object_->material;
        if (material) {
            update_direction();
            material->rotation -= rotation_speed_ * dt;
        }
    }

    //Thrust is a scalar that is multiplied into the direction vector
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

    virtual bool check_collision(const std::shared_ptr<ObjectController>& other) {
        auto other_object = other->get_sprite();
        auto this_object = this->get_sprite();

        // assuming the sprites position is at its center
        float this_left = this_object->position.x - (this_object->scale.x / 2);
        float this_right = this_object->position.x + (this_object->scale.x / 2);
        float this_top = this_object->position.y - (this_object->scale.y / 2);
        float this_bottom = this_object->position.y + (this_object->scale.y / 2);

        float other_left = other_object->position.x - (other_object->scale.x / 2);
        float other_right = other_object->position.x + (other_object->scale.x / 2);
        float other_top = other_object->position.y - (other_object->scale.y / 2);
        float other_bottom = other_object->position.y + (other_object->scale.y / 2);

        // check if bounding boxes intersect
        // returns true if collision
        return this_left < other_right && this_right > other_left &&
               this_top < other_bottom && this_bottom > other_top;
    }

    //getters

    virtual Vector2 get_velocity() {
        return velocity_;
    }

    virtual Vector2 get_direction() {
        return direction_;
    }

    virtual float get_rotation_speed() {
        return rotation_speed_;
    }

    virtual std::shared_ptr<Sprite> get_sprite() {
        return object_;
    }

    //setters

    virtual void set_velocity(const Vector2& velocity) {
        velocity_ = velocity;
    }

    virtual void set_direction(const Vector2& direction) {
        direction_ = direction;
    }

    virtual void set_rotation_speed(float& rotation_speed) {
        rotation_speed_ = rotation_speed;
    }



private:

    virtual void update_direction() {
        auto material = object_->material;
        if (material) {
            float theta = material->rotation + (2 * atanf(1)); // (atanf(1) * 4) = pi
            direction_.x = cosf(theta);
            direction_.y = sinf(theta);
        }
    }

    std::shared_ptr<Sprite> object_;
    Vector2 direction_;
    Vector2 velocity_;
    float velocity_float_;
    float rotation_speed_;
    float thrust_power_;
    float friction_coefficient_;

};

#endif//ASTEROIDS_OBJECT_CONTROLLER_HPP