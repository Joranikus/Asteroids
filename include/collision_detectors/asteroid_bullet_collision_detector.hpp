
#ifndef ASTEROIDS_ASTEROID_BULLET_COLLISON_DETECTOR_HPP
#define ASTEROIDS_ASTEROID_BULLET_COLLISON_DETECTOR_HPP

#include "collision_detectors/base_collision_detector.hpp"

using namespace threepp;

class AsteroidBulletCollisionDetector: public BaseCollisionDetector {

public:
    void check_collision(std::vector<std::shared_ptr<BaseController>>& bullet_list,
                         std::vector<std::shared_ptr<BaseController>>& asteroid_list);
};

#endif//ASTEROIDS_ASTEROID_BULLET_COLLISON_DETECTOR_HPP
