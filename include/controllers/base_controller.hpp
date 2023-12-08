
#ifndef ASTEROIDS_BASE_CONTROLLER_HPP
#define ASTEROIDS_BASE_CONTROLLER_HPP

#include "threepp/threepp.hpp"

class BaseController {

public:
    BaseController(const std::shared_ptr<threepp::Sprite>& sprite,
                   threepp::Vector2 direction,
                   float rotation_speed = 0.0f,
                   float friction_coefficient = 0.0f,
                   float thrust_power = 0.0f,
                   float initial_velocity = 0.0f,
                   float initial_rotation_velocity = 0.0f);

    virtual void update(float dt);
    virtual void rotate_counter_clockwise(float dt);
    virtual void rotate_clockwise(float dt);
    virtual void thrust_forward(float dt);
    virtual void thrust_backward(float dt);

    virtual threepp::Vector2 get_position() const;
    virtual threepp::Vector2 get_velocity() const;
    virtual threepp::Vector2 get_direction() const;
    virtual float get_rotation() const;
    virtual float get_rotation_speed() const;
    virtual float get_friction_coefficient() const;
    virtual float get_mass() const;

    virtual void set_position(threepp::Vector2 position);
    virtual void set_velocity(threepp::Vector2 velocity);
    virtual void set_direction(threepp::Vector2 direction);
    virtual void set_rotation(float radian);
    virtual void set_rotation_speed(float rotation_speed);
    virtual void set_friction_coefficient(float friction_coefficient);

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

    float mass;
    threepp::Vector2 velocity_;
};

#endif//ASTEROIDS_BASE_CONTROLLER_HPP