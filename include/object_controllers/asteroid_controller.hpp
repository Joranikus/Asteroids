
#ifndef ASTEROIDS_ASTEROID_CONTROLLER_HPP
#define ASTEROIDS_ASTEROID_CONTROLLER_HPP

#include "functions/random_functions.hpp"
#include "object_controller.hpp"
#include "threepp/threepp.hpp"

using namespace threepp;

class AsteroidController: public PhysicsController {

public:

    AsteroidController(const std::shared_ptr<Sprite>& asteroid_sprite, WindowSize& screen_size, float edge_offset, float min_velocity, float max_velocity)
        : PhysicsController(asteroid_sprite, random_direction(), random_float(min_velocity, max_velocity), 0, 0, 0),
          screen_size_(screen_size), edge_offset_(edge_offset)
    {
        //1 = top edge, 2 = right edge, 3 = bottom edge, 4 = left edge
        int edge = random_int(1, 4);
        int edge_position;

        switch (edge) {
            case 1:
            case 3:
                edge_position = random_int(0, screen_size.width);
                break;
            case 2:
            case 4:
                edge_position = random_int(0, screen_size.height);
                break;
        }

        switch (edge) {
            case 1: // top
                asteroid_sprite->position.x = edge_position;
                asteroid_sprite->position.y = -edge_offset_;
                break;
            case 2: // right
                asteroid_sprite->position.x = screen_size_.width + edge_offset_;
                asteroid_sprite->position.y = edge_position;
                break;
            case 3: // bottom
                asteroid_sprite->position.x = edge_position;
                asteroid_sprite->position.y = screen_size_.height + edge_offset_;
                break;
            case 4: // left
                asteroid_sprite->position.x = -edge_offset_;
                asteroid_sprite->position.y = edge_position;
                break;
        }
    }

    std::shared_ptr<Sprite> get_sprite() override {
        return PhysicsController::get_sprite();
    }

    void update(float dt) override {
        PhysicsController::update(dt);
    }

private:

    WindowSize& screen_size_;
    float edge_offset_;

};

#endif//ASTEROIDS_ASTEROID_CONTROLLER_HPP
