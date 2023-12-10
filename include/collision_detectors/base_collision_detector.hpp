
#ifndef ASTEROIDS_BASE_COLLISION_DETECTOR_HPP
#define ASTEROIDS_BASE_COLLISION_DETECTOR_HPP

#include "controllers/base_controller.hpp"

class BaseCollisionDetector {

public:
    virtual bool collision(const std::shared_ptr<BaseController>& object_1,
                           const std::shared_ptr<BaseController>& object_2);

};

#endif//ASTEROIDS_BASE_COLLISION_DETECTOR_HPP
