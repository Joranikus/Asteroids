
#include "asteroid_controller.hpp"
#include "functions/random_functions.hpp"

using namespace threepp;

AsteroidController::AsteroidController(const std::shared_ptr<Sprite>& asteroid_sprite,
                                       WindowSize& screen_size,
                                       Vector2 direction,
                                       float initial_rotation_speed,
                                       float min_velocity,
                                       float max_velocity,
                                       float edge_offset)

    : BaseController(asteroid_sprite,
                     direction,
                     0,
                     0,
                     0,
                     random_float(min_velocity, max_velocity),
                     initial_rotation_speed),

      screen_size_(screen_size),
      edge_offset_(edge_offset) {

    enum class Edge { Left,
                      Right,
                      Top,
                      Bottom };
    Edge edge;

    // determines the edge based on the direction
    if (fabs(direction.x) > fabs(direction.y)) {
        edge = (direction.x > 0) ? Edge::Left : Edge::Right;
    } else {
        edge = (direction.y > 0) ? Edge::Bottom : Edge::Top;
    }

    // positions the asteroid based on the chosen edge
    switch (edge) {
        case Edge::Left:
            asteroid_sprite->position.x = -screen_size_.width / 2 - edge_offset_;
            asteroid_sprite->position.y = random_float(-screen_size_.height / 2, screen_size_.height / 2);
            break;
        case Edge::Right:
            asteroid_sprite->position.x = screen_size_.width / 2 + edge_offset_;
            asteroid_sprite->position.y = random_float(-screen_size_.height / 2, screen_size_.height / 2);
            break;
        case Edge::Top:
            asteroid_sprite->position.y = screen_size_.height / 2 + edge_offset_;
            asteroid_sprite->position.x = random_float(-screen_size_.width / 2, screen_size_.width / 2);
            break;
        case Edge::Bottom:
            asteroid_sprite->position.y = -screen_size_.height / 2 - edge_offset_;
            asteroid_sprite->position.x = random_float(-screen_size_.width / 2, screen_size_.width / 2);
            break;
    }
}