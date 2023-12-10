
#include "base_controller.hpp"
#include <cmath>

using namespace threepp;

BaseController::BaseController(const std::shared_ptr<Sprite>& sprite,
                               Vector2 direction,
                               float rotation_speed,
                               float friction_coefficient,
                               float thrust_power,
                               float initial_velocity,
                               float initial_rotation_velocity)

    : sprite_(sprite),
      direction_(direction),
      rotation_speed_(rotation_speed),
      friction_coefficient_(friction_coefficient),
      thrust_power_(thrust_power),
      velocity_float_(initial_velocity),
      initial_rotation_velocity_(initial_rotation_velocity) {

    // these check if the class is initiated correctly with correct values
    if (!sprite) {
        throw std::runtime_error("Sprite not found");
    }

    if (!sprite->material) {
        throw std::runtime_error("Sprite material not found");
    }

    if (std::abs(direction.length() - 1.0f) > 0.001) {// because direction vector always has a length of 1
        throw std::invalid_argument("Direction vector must be normalized");
    }

    if (rotation_speed < 0) {//rotation speed cant be negative
        throw std::invalid_argument("Rotation speed must be positive");
    }

    if (friction_coefficient < 0.0f || friction_coefficient > 1.0f) {// 0 = no friction, 1 = all the friction
        throw std::invalid_argument("Friction coefficient must be between 0 and 1.");
    }

    if (thrust_power < 0) {// an engine can't have negative horsepower
        throw std::invalid_argument("Thrust power must be positive");
    }

    // creates mass according to material size
    int width = static_cast<int>(sprite->material->map->image->width);
    int height = static_cast<int>(sprite->material->map->image->width);
    mass = static_cast<float>(width * height * 0.01);

    // used for initial velocity so that the object moves when created
    velocity_.x = direction_.x * velocity_float_;
    velocity_.y = direction_.y * velocity_float_;
}

// uses DT to move object relative to time
void BaseController::update(float dt) {
    velocity_.x -= friction_coefficient_ * velocity_.x * dt;
    velocity_.y -= friction_coefficient_ * velocity_.y * dt;

    sprite_->position.x += velocity_.x * dt;
    sprite_->position.y += velocity_.y * dt;

    // I decided to not let rotation be effected by friction
    sprite_->material->rotation += initial_rotation_velocity_ * dt;
}

void BaseController::rotate_counter_clockwise(float dt) {
    update_direction();
    sprite_->material->rotation += rotation_speed_ * dt;
}

void BaseController::rotate_clockwise(float dt) {
    update_direction();
    sprite_->material->rotation -= rotation_speed_ * dt;
}

// thrust is a scalar that is multiplied into the direction vector
void BaseController::thrust_forward(float dt) {
    update_direction();
    velocity_.x += direction_.x * thrust_power_ * dt;
    velocity_.y += direction_.y * thrust_power_ * dt;
}

void BaseController::thrust_backward(float dt) {
    update_direction();
    velocity_.x -= direction_.x * thrust_power_ * dt;
    velocity_.y -= direction_.y * thrust_power_ * dt;
}

// getters
Vector2 BaseController::get_position() const {
    return {sprite_->position.x, sprite_->position.y};
}

Vector2 BaseController::get_velocity() const {
    return velocity_;
}

Vector2 BaseController::get_direction() const {
    return direction_;
}

float BaseController::get_rotation() const {
    return sprite_->material->rotation;
}

float BaseController::get_rotation_speed() const {
    return rotation_speed_;
}

float BaseController::get_friction_coefficient() const {
    return friction_coefficient_;
}

float BaseController::get_mass() const {
    return mass;
}

// setters
void BaseController::set_position(Vector2 position) {
    sprite_->position.x = position.x;
    sprite_->position.y = position.y;
}

void BaseController::set_velocity(Vector2 velocity) {
    velocity_ = velocity;
}

void BaseController::set_direction(Vector2 direction) {
    if (std::abs(direction.length() - 1.0f) > 0.001) {
        throw std::invalid_argument("Direction vector must be normalized");
    }
    direction_ = direction;
}

void BaseController::set_rotation(const float radian) {
    sprite_->material->rotation = radian;
}

void BaseController::set_rotation_speed(const float rotation_speed) {
    rotation_speed_ = rotation_speed;
}

void BaseController::set_friction_coefficient(float friction_coefficient) {
    friction_coefficient_ = friction_coefficient;
}

// using trigonometry to get direction
void BaseController::update_direction() {
    float theta = sprite_->material->rotation + (2 * atanf(1));// (atanf(1) * 4) = pi
    direction_.x = cosf(theta);
    direction_.y = sinf(theta);
}