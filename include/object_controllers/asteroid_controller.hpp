
#ifndef ASTEROIDS_ASTEROID_CONTROLLER_HPP
#define ASTEROIDS_ASTEROID_CONTROLLER_HPP

#include "functions/random_functions.hpp"
#include "object_controller.hpp"
#include "threepp/threepp.hpp"

using namespace threepp;

class AsteroidController: public ObjectController {

public:
    enum class Edge { Left, Right, Top, Bottom };

    AsteroidController(const std::shared_ptr<Sprite>& asteroid_sprite, WindowSize& screen_size, Vector2 direction, float edge_offset, float min_velocity, float max_velocity)
        : ObjectController(asteroid_sprite, direction, random_float(min_velocity, max_velocity), 0, 0, 0),
          screen_size_(screen_size), edge_offset_(edge_offset)
    {
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

    std::shared_ptr<Sprite> get_sprite() override {
        return ObjectController::get_sprite();
    }

    void update(float dt) override {
        ObjectController::update(dt);
    }

private:
    WindowSize& screen_size_;
    float edge_offset_;
};

#endif//ASTEROIDS_ASTEROID_CONTROLLER_HPP
