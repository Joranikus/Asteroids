
#include "base_collision_detector.hpp"
#include <cmath>

// fikk help av ChatGPT til å skrive denne
bool BaseCollisionDetector::collision(const std::shared_ptr<BaseController>& object_1,
                                      const std::shared_ptr<BaseController>& object_2) {

    if (!object_1 || !object_2) {
        throw std::runtime_error("Object not found");
    }

    if (!object_1->sprite_ || !object_2->sprite_) {
        throw std::runtime_error("Object material not found");
    }

    auto other_object = object_2->sprite_;
    auto this_object = object_1->sprite_;

    // calculates the radius (assuming radius is half of the scale)
    float radius1 = std::max(this_object->scale.x, this_object->scale.y) / 2;
    float radius2 = std::max(other_object->scale.x, other_object->scale.y) / 2;

    // calculates the distance between the centers
    float dx = this_object->position.x - other_object->position.x;
    float dy = this_object->position.y - other_object->position.y;
    float distance = std::sqrt(dx * dx + dy * dy);

    // checks if the distance is less than or equal to the sum of the radius
    return distance <= (radius1 + radius2);
}