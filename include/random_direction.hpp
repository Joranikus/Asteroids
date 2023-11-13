
#include "threepp/threepp.hpp"
#include <random>

using namespace threepp;

#ifndef ASTEROIDS_RANDOM_DIRECTION_HPP
#define ASTEROIDS_RANDOM_DIRECTION_HPP

Vector2 random_direction() {
    std::random_device rd;
    std::mt19937 gen(rd());

    float min = 0;
    float max = math::TWO_PI;

    std::uniform_real_distribution<> distr(min, max);

    auto random = distr(gen);

    Vector2 direction;
    direction.x = cos(random);
    direction.y = sin(random);

    return direction;
}

#endif//ASTEROIDS_RANDOM_DIRECTION_HPP
