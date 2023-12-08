
#include "particle_controller.hpp"

ParticleController::ParticleController(std::shared_ptr<threepp::Sprite> const& particle_sprite,
                                       threepp::Vector2 direction,
                                       float initial_velocity)

    : BaseController(particle_sprite,
                     direction,
                     0,
                     0,
                     0,
                     initial_velocity) {}
