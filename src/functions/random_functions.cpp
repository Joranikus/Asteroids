#include "functions/random_functions.hpp"
#include <random>

using namespace threepp;

Vector2 random_direction() {
    std::random_device rd;
    std::mt19937 gen(rd());

    float min = 0;
    float max = math::TWO_PI;

    std::uniform_real_distribution<> distr(min, max);

    auto random = static_cast<float>(distr(gen));

    Vector2 direction;
    direction.x = cosf(random);
    direction.y = sinf(random);

    return direction;
}

float random_float(float min, float max) {
    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_real_distribution<> distr(min, max);

    return distr(gen);
}

int random_int(int min, int max) {
    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_int_distribution distr(min, max);

    return distr(gen);
}
