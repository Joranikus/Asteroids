
#ifndef ASTEROIDS_GAME_HPP
#define ASTEROIDS_GAME_HPP

#include "factories/asteroid_factory.hpp"
#include "functions/create_sprite.hpp"
#include "controllers/spaceship_controller.hpp"
#include "threepp/threepp.hpp"
#include "collision_detectors/asteroid_bullet_collision_detector.hpp"
using namespace threepp;

class Game {

public:

    void setup();

    void run();

    void pause();

private:

};

#endif//ASTEROIDS_GAME_HPP
