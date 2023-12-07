
#include "bullet_controller.hpp"

BulletController::BulletController(std::shared_ptr<threepp::Sprite> const& bullet_sprite,
                                   threepp::Vector2 direction,
                                   float initial_velocity)

    : BaseController(bullet_sprite,
                     direction,
                     0,
                     0,
                     0,
                     initial_velocity) {}