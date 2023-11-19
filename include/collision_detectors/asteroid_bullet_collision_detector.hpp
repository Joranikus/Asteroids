
#include "threepp/threepp.hpp"
#include "collision_detectors/base_collision_detector.hpp"
#include "factories/base_factory.hpp"

using namespace threepp;

#ifndef ASTEROIDS_ASTEROID_BULLET_COLLISON_DETECTOR_HPP
#define ASTEROIDS_ASTEROID_BULLET_COLLISON_DETECTOR_HPP

class AsteroidBulletCollisionDetector : public BaseCollisionDetector {

public:

    void check_collision(std::vector<std::shared_ptr<BaseController>> bullet_list, std::vector<std::shared_ptr<BaseController>> asteroid_list) {
        for (auto& bullet : bullet_list) {
            for (auto& asteroid : asteroid_list) {
                if (collision(bullet, asteroid)) {
                    bullet->set_mark_for_removal();
                    asteroid->set_mark_for_removal();
                }
            }
        }
    }

private:

};

#endif//ASTEROIDS_ASTEROID_BULLET_COLLISON_DETECTOR_HPP
