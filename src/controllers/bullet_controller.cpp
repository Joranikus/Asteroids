
#include "bullet_controller.hpp"

using namespace threepp;

BulletController::BulletController(const std::shared_ptr<Sprite>& bullet_sprite,
                                   Vector2 direction,
                                   float initial_velocity)

    : BaseController(bullet_sprite,
                     direction,
                     0,
                     0,
                     0,
                     initial_velocity) {}