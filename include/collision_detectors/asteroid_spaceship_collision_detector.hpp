
#ifndef ASTEROIDS_ASTEROID_SPACESHIP_COLLISION_DETECTOR_HPP
#define ASTEROIDS_ASTEROID_SPACESHIP_COLLISION_DETECTOR_HPP

#include "elastic_collision_detector.hpp"
#include "controllers/base_controller.hpp"

class AsteroidSpaceshipCollisionDetector : public ElasticCollisionDetector {

public:
    void asteroid_spaceship_collision_check(std::vector<std::shared_ptr<BaseController>>& asteroid_list,
                                            std::shared_ptr<BaseController> spaceship);

private:
    static void collision_damage(std::shared_ptr<BaseController>& asteroid,
                                 std::shared_ptr<BaseController> spaceship);

    static float calculate_damage(float asteroid_mass, float spaceship_mass);
};

#endif//ASTEROIDS_ASTEROID_SPACESHIP_COLLISION_DETECTOR_HPP