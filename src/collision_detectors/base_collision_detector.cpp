
#include "base_collision_detector.hpp"

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

    // assuming the sprites position is at its center
    float this_left = this_object->position.x - (this_object->scale.x / 2);
    float this_right = this_object->position.x + (this_object->scale.x / 2);
    float this_top = this_object->position.y - (this_object->scale.y / 2);
    float this_bottom = this_object->position.y + (this_object->scale.y / 2);

    float other_left = other_object->position.x - (other_object->scale.x / 2);
    float other_right = other_object->position.x + (other_object->scale.x / 2);
    float other_top = other_object->position.y - (other_object->scale.y / 2);
    float other_bottom = other_object->position.y + (other_object->scale.y / 2);

    // check if bounding boxes intersect
    // returns true if collision
    return this_left < other_right && this_right > other_left &&
           this_top < other_bottom && this_bottom > other_top;
}
