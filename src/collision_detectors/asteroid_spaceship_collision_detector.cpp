
#include "asteroid_spaceship_collision_detector.hpp"

void AsteroidSpaceshipCollisionDetector::asteroid_spaceship_collision_check(std::vector<std::shared_ptr<BaseController>>& asteroid_list,
                                                                            std::shared_ptr<BaseController> spaceship) {
    for (auto& asteroid : asteroid_list) {
        if (collision(asteroid, spaceship)) {
            auto new_velocities = calculate_collision(asteroid, spaceship);

            asteroid->set_velocity(new_velocities.first);
            spaceship->set_velocity(new_velocities.second);

            collision_damage(asteroid, spaceship);

            if (spaceship->get_health() <= 0) {
                spaceship->marked_for_removal = true;
            }
        }
    }
}

void AsteroidSpaceshipCollisionDetector::collision_damage(std::shared_ptr<BaseController>& asteroid,
                                                         std::shared_ptr<BaseController> spaceship) {
    float asteroid_mass = asteroid->get_mass();
    float spaceship_mass = spaceship->get_mass();

    threepp::Vector2 relative_velocity = asteroid->get_velocity() - spaceship->get_velocity();
    float velocity_magnitude = relative_velocity.length();

    int damage = static_cast<int>(calculate_damage(asteroid_mass, spaceship_mass, velocity_magnitude));

    int new_health = static_cast<int>(std::max(spaceship->get_health() - damage, 0));
    spaceship->set_health(new_health);
}

float AsteroidSpaceshipCollisionDetector::calculate_damage(float asteroid_mass, float spaceship_mass, float velocity_magnitude) {
    const float base_damage_percent = 5.0f;
    const float mass_ratio_coefficient = 0.5f;
    const float velocity_factor = 0.05f;

    float mass_ratio = asteroid_mass / spaceship_mass;

    float damage_percent = base_damage_percent + (mass_ratio_coefficient * mass_ratio * base_damage_percent)
                           + (velocity_factor * velocity_magnitude);

    // checks that the damage is within 0 to 100%
    return std::min(std::max(damage_percent, 0.0f), 100.0f);
}