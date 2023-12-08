
#ifndef ASTEROIDS_PARTICLE_CONTROLLER_HPP
#define ASTEROIDS_PARTICLE_CONTROLLER_HPP

#include "base_controller.hpp"
#include "threepp/threepp.hpp"

class ParticleController: public BaseController {

public:
    ParticleController(std::shared_ptr<threepp::Sprite> const& particle_sprite,
                       threepp::Vector2 direction,
                       float initial_velocity);
};

#endif//ASTEROIDS_PARTICLE_CONTROLLER_HPP
