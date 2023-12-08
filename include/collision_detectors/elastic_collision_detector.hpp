
#ifndef ASTEROIDS_ASTEROID_COLLISON_DETECTOR_HPP
#define ASTEROIDS_ASTEROID_COLLISON_DETECTOR_HPP

#include "base_collision_detector.hpp"
#include "threepp/threepp.hpp"

class ElasticCollisionDetector: public BaseCollisionDetector {

public:
    void check_collision(std::vector<std::shared_ptr<BaseController>>& asteroid_list);
    std::pair<threepp::Vector2, threepp::Vector2> calculate_collision(std::shared_ptr<BaseController>& this_object,
                                                                      std::shared_ptr<BaseController>& other_object);

    threepp::Vector2 calculate_collision_vector(const std::shared_ptr<BaseController>& object_1, const std::shared_ptr<BaseController>& object_2);
    float calculate_dot_product(const threepp::Vector2& velocity, const threepp::Vector2& collision_normalized);

    std::pair<threepp::Vector2, threepp::Vector2> calculate_new_velocities(const threepp::Vector2& v0_this,
                                                                           const threepp::Vector2& v0_other, float p,
                                                                           float mass_this, float mass_other,
                                                                           const threepp::Vector2& collision_normal);
};

#endif//ASTEROIDS_ASTEROID_COLLISON_DETECTOR_HPP
