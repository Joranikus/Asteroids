
#ifndef ASTEROIDS_ASTEROID_CONTROLLER_HPP
#define ASTEROIDS_ASTEROID_CONTROLLER_HPP

#include "base_controller.hpp"
#include "threepp/threepp.hpp"

class AsteroidController: public BaseController {

public:
    AsteroidController(const std::shared_ptr<threepp::Sprite>& asteroid_sprite,
                       threepp::WindowSize& screen_size,
                       threepp::Vector2 direction,
                       float initial_rotation_speed,
                       float min_velocity,
                       float max_velocity,
                       float edge_offset);

private:
    threepp::WindowSize& screen_size_;
    const float edge_offset_;
};

#endif//ASTEROIDS_ASTEROID_CONTROLLER_HPP