
#ifndef ASTEROIDS_PARTICLE_CONTROLLER_HPP
#define ASTEROIDS_PARTICLE_CONTROLLER_HPP

#include "base_controller.hpp"
#include "threepp/threepp.hpp"

class ParticleController: public BaseController {

public:
    ParticleController(std::shared_ptr<threepp::Sprite> const& particle_sprite,
                       threepp::Vector2 direction,
                       float initial_velocity,
                       float initial_rotation_velocity,
                       float friction_coefficient,
                       float life_time);

    void update(float dt) override;

private:
    std::shared_ptr<threepp::Sprite> const& particle_sprite_;
    float life_time_ = 0.0;

    float time_elapsed = 0.0f;
};

#endif//ASTEROIDS_PARTICLE_CONTROLLER_HPP
