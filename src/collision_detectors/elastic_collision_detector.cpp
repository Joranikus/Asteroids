
#include "elastic_collision_detector.hpp"

using namespace threepp;

// formel for elastisk kollisjon hentet fra https://www.101computing.net/elastic-collision-in-a-pool-game/.
// checks collision between all the asteroids
void ElasticCollisionDetector::check_collision_list(std::vector<std::shared_ptr<BaseController>>& object_list) {
    for (size_t i = 0; i < object_list.size(); ++i) {
        for (size_t j = i + 1; j < object_list.size(); ++j) {
            auto& this_object = object_list[i];
            auto& other_object = object_list[j];

            if (collision(this_object, other_object)) {
                auto new_velocities = calculate_collision(this_object, other_object);

                this_object->set_velocity(new_velocities.first);
                other_object->set_velocity(new_velocities.second);
            }
        }
    }
}

// inspirert fra koden til 101computing og med hjelp fra ChatGPT
// uses kinetic physics formula to calculate the new direction and velocity of the two objects
std::pair<Vector2, Vector2> ElasticCollisionDetector::calculate_collision(std::shared_ptr<BaseController>& this_object,
                                                                           std::shared_ptr<BaseController>& other_object) {

    if (!this_object || !other_object) {
        throw std::runtime_error("Object doesn't exist");
    }

    Vector2 v0_this = this_object->get_velocity();
    Vector2 v0_other = other_object->get_velocity();

    float mass_this = this_object->get_mass();
    float mass_other = other_object->get_mass();

    Vector2 collision_vector = calculate_collision_vector(this_object, other_object);
    Vector2 collision_normalized = collision_vector.normalize();

    float this_dot_collision_normal = calculate_dot_product(v0_this, collision_normalized);
    float other_dot_collision_normal = calculate_dot_product(v0_other, collision_normalized);

    if (this_dot_collision_normal - other_dot_collision_normal < 0) {
        return {v0_this, v0_other};
    }

    float p = 2 * (this_dot_collision_normal - other_dot_collision_normal) / (mass_this + mass_other);

    return calculate_new_velocities(v0_this, v0_other, p, mass_this, mass_other, collision_normalized);
}

Vector2 ElasticCollisionDetector::calculate_collision_vector(const std::shared_ptr<BaseController>& object_1, const std::shared_ptr<BaseController>& object_2) {
    return {object_2->get_position().x - object_1->get_position().x, object_2->get_position().y - object_1->get_position().y};
}

float ElasticCollisionDetector::calculate_dot_product(const Vector2& velocity, const Vector2& collision_normalized) {
    return (velocity.x * collision_normalized.x) + (velocity.y * collision_normalized.y);
}

std::pair<Vector2, Vector2> ElasticCollisionDetector::calculate_new_velocities(const Vector2& v0_this, const Vector2& v0_other, float p,
                                                                                float mass_this, float mass_other, const Vector2& collision_normal) {
    Vector2 v_this = {v0_this.x - collision_normal.x * p * mass_other, v0_this.y - collision_normal.y * p * mass_other};
    Vector2 v_other = {v0_other.x + collision_normal.x * p * mass_this, v0_other.y + collision_normal.y * p * mass_this};
    return {v_this, v_other};
}
