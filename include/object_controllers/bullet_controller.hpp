
#ifndef ASTEROIDS_BULLET_CONTROLLER_HPP
#define ASTEROIDS_BULLET_CONTROLLER_HPP

#include "base_controller.hpp"
#include "threepp/threepp.hpp"

using namespace threepp;

class BulletController: public BaseController {

public:
    BulletController(const std::shared_ptr<Sprite>& bullet_sprite, Vector2 direction, float initial_velocity)
        : BaseController(bullet_sprite, direction, initial_velocity, 0, 0, 0) {}
};

#endif//ASTEROIDS_BULLET_CONTROLLER_HPP