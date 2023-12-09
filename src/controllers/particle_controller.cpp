
#include "particle_controller.hpp"

ParticleController::ParticleController(std::shared_ptr<threepp::Sprite> const& particle_sprite,
                                       threepp::Vector2 direction,
                                       float initial_velocity,
                                       float initial_rotation_velocity,
                                       float friction_coefficient,
                                       float life_time)

    : BaseController(particle_sprite,
                     direction,
                     0,
                     friction_coefficient,
                     0,
                     initial_velocity,
                     initial_rotation_velocity),

      particle_sprite_(particle_sprite),
      life_time_(life_time) {}

void ParticleController::update(float dt) {
    BaseController::update(dt);
    time_elapsed += dt;

    particle_sprite_->material->opacity = 100 * (1 - (time_elapsed / life_time_));

    if (time_elapsed > life_time_) {
        marked_for_removal = true;
    }
}
