
#ifndef ASTEROIDS_ASTEROID_BULLET_COLLISON_DETECTOR_HPP
#define ASTEROIDS_ASTEROID_BULLET_COLLISON_DETECTOR_HPP

#include "collision_detectors/base_collision_detector.hpp"

class AsteroidBulletCollisionDetector: public BaseCollisionDetector {

public:
    void check_collision(std::vector<std::shared_ptr<BaseController>>& bullet_list,
                         std::vector<std::shared_ptr<BaseController>>& asteroid_list);

    int get_score() const;

private:
    int score;
};

#endif//ASTEROIDS_ASTEROID_BULLET_COLLISON_DETECTOR_HPP