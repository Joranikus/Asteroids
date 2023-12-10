
#include "particle_factory.hpp"
#include "particle_controller.hpp"
#include "functions/random_functions.hpp"
#include <cmath>

#include <utility>

using namespace threepp;

ParticleFactory::ParticleFactory(threepp::Canvas& canvas,
                                 std::shared_ptr<threepp::Scene>& scene,
                                 TextureLoader& loader,
                                 std::string material_path,
                                 float scale,
                                 float velocity,
                                 float friction_coefficient,
                                 float angle_spread,
                                 float life_time)

    : BaseFactory(canvas,
                  scene,
                  loader,
                  std::move(material_path),
                  scale),

      canvas_(canvas),
      loader_(loader),
      material_path_(std::move(material_path)),
      velocity_(velocity),
      friction_coefficient_(friction_coefficient),
      angle_spread_(angle_spread),
      scale_(scale),
      life_time_(life_time) {}

void ParticleFactory::generate_particle(Vector2 direction, Vector2 position) {
    auto particle_sprite = create_object_sprite();
    set_particle_position(particle_sprite, position);

    auto particle = create_particle_object(particle_sprite, direction);
    add_to_scene(particle_sprite);
}

void ParticleFactory::generate_particle_burst(Vector2 middle_position, Vector2 general_direction, float burst_radius, int number_of_particles) {

    float general_direction_angle = std::atan2(general_direction.y, general_direction.x);
    float angle_spread_radian = (angle_spread_ * (math::PI / 180));

    for (int i = 0; i < number_of_particles; ++i) {
        float angle_offset = random_float((-angle_spread_radian / 2), (angle_spread_radian / 2));
        float angle_radian = general_direction_angle + angle_offset;

        Vector2 offset_position = {
                burst_radius * std::cos(angle_radian),
                burst_radius * std::sin(angle_radian)
        };

        Vector2 start_position = middle_position + offset_position;

        Vector2 particle_direction = {
                std::cos(angle_radian),
                std::sin(angle_radian)
        };

        generate_particle(particle_direction, start_position);
    }
}

void ParticleFactory::set_particle_position(std::shared_ptr<threepp::Sprite>& particle_sprite, Vector2 position) {
    particle_sprite->position.x = position.x;
    particle_sprite->position.y = position.y;
}

std::shared_ptr<BaseController> ParticleFactory::create_particle_object(std::shared_ptr<Sprite>& object_sprite, Vector2 direction) {
    float random_rotation_speed = random_float(-20, 20);

    auto particle = std::make_shared<ParticleController>(object_sprite,
                                                         direction,
                                                         velocity_,
                                                         random_rotation_speed,
                                                         friction_coefficient_,
                                                         life_time_);

    objects.emplace_back(particle);
    return particle;
}