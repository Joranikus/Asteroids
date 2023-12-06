
#ifndef ASTEROIDS_BASE_CONTROLLER_HPP
#define ASTEROIDS_BASE_CONTROLLER_HPP

#include "threepp/threepp.hpp"
#include <cmath>

class BaseController {

public:
    BaseController(const std::shared_ptr<threepp::Sprite>& sprite,
                   threepp::Vector2 direction,
                   float rotation_speed = 0.0f,
                   float friction_coefficient = 0.0f,
                   float thrust_power = 0.0f,
                   float initial_velocity = 0.0f,
                   float initial_rotation_velocity = 0.0f);

    virtual void update(const float dt);
    virtual void rotate_counter_clockwise(const float dt);
    virtual void rotate_clockwise(const float dt);
    virtual void thrust_forward(const float dt);
    virtual void thrust_backward(const float dt);

    virtual threepp::Vector2 get_position() const;
    virtual threepp::Vector2 get_velocity() const;
    virtual threepp::Vector2 get_direction() const;
    virtual float get_rotation_speed() const;

    virtual void set_position(const threepp::Vector2 position);
    virtual void set_velocity(const threepp::Vector2& velocity);
    virtual void set_direction(const threepp::Vector2& direction);
    virtual void set_rotation_speed(const float rotation_speed);

    std::shared_ptr<threepp::Sprite> sprite_;
    bool marked_for_removal = false;

private:
    void update_direction();

    threepp::Vector2 direction_;
    float rotation_speed_;
    float friction_coefficient_;
    float thrust_power_;
    float velocity_float_;
    float initial_rotation_velocity_;

    threepp::Vector2 velocity_;
};

#endif//ASTEROIDS_BASE_CONTROLLER_HPP