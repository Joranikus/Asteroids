
#include "asteroid_controller.hpp"
#include "functions/random_functions.hpp"
#include <cmath>

using namespace threepp;

AsteroidController::AsteroidController(const std::shared_ptr<Sprite>& asteroid_sprite,
                                       WindowSize& screen_size,
                                       Vector2 direction,
                                       float initial_rotation_speed,
                                       const float min_velocity,
                                       const float max_velocity,
                                       const float edge_offset)

    : BaseController(asteroid_sprite,
                     direction,
                     0,
                     0,
                     0,
                     random_float(min_velocity, max_velocity),
                     initial_rotation_speed),

      screen_size_(screen_size),
      edge_offset_(edge_offset) {

    if (min_velocity < 0 || max_velocity < 0) {
        throw std::invalid_argument("Asteroid velocity can't be negative, it has to fly towards screen");
    }

    enum class Edge { Left,
                      Right,
                      Top,
                      Bottom };
    Edge edge;

    // determines the edge based on the direction
    if (std::fabs(direction.x) > std::fabs(direction.y)) {
        edge = (direction.x > 0) ? Edge::Left : Edge::Right;
    } else {
        edge = (direction.y > 0) ? Edge::Bottom : Edge::Top;
    }

    // positions the asteroid based on the chosen edge
    // edge offset is used such that if I have an edge offset of 50, the object spawns 50 pixels outside the screen edge
    switch (edge) {
        case Edge::Left:
            asteroid_sprite->position.x = static_cast<float>(-screen_size_.width) / 2 - edge_offset_;
            asteroid_sprite->position.y = random_float(static_cast<float>(-screen_size_.height) / 2,
                                                       static_cast<float>(screen_size_.height) / 2);
            break;
        case Edge::Right:
            asteroid_sprite->position.x = static_cast<float>(screen_size_.width) / 2 + edge_offset_;
            asteroid_sprite->position.y = random_float(static_cast<float>(-screen_size_.height) / 2,
                                                       static_cast<float>(screen_size_.height) / 2);
            break;
        case Edge::Top:
            asteroid_sprite->position.y = static_cast<float>(screen_size_.height) / 2 + edge_offset_;
            asteroid_sprite->position.x = random_float(static_cast<float>(-screen_size_.width) / 2,
                                                       static_cast<float>(screen_size_.width) / 2);
            break;
        case Edge::Bottom:
            asteroid_sprite->position.y = static_cast<float>(-screen_size_.height) / 2 - edge_offset_;
            asteroid_sprite->position.x = random_float(static_cast<float>(-screen_size_.width) / 2,
                                                       static_cast<float>(screen_size_.width) / 2);
            break;
    }
}