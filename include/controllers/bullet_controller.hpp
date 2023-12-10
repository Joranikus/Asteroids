
#ifndef ASTEROIDS_BULLET_CONTROLLER_HPP
#define ASTEROIDS_BULLET_CONTROLLER_HPP

#include "base_controller.hpp"
#include "threepp/threepp.hpp"

class BulletController: public BaseController {

public:
    BulletController(std::shared_ptr<threepp::Sprite> const& bullet_sprite,
                     threepp::Vector2 direction,
                     float initial_velocity);
};

#endif//ASTEROIDS_BULLET_CONTROLLER_HPP