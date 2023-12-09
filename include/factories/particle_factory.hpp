
#ifndef ASTEROIDS_PARTICLE_FACTORY_HPP
#define ASTEROIDS_PARTICLE_FACTORY_HPP

#include "threepp/threepp.hpp"
#include "base_factory.hpp"

class ParticleFactory : public BaseFactory {

public:
    ParticleFactory(threepp::Canvas& canvas,
                    std::shared_ptr<threepp::Scene>& scene,
                    threepp::TextureLoader& loader,
                    std::string material_path,
                    float velocity,
                    float friction_coefficient,
                    float angle_spread,
                    float scale,
                    float life_time);

    void generate_particle(threepp::Vector2 direction, threepp::Vector2 position);
    void generate_particle_burst(threepp::Vector2 middle_position, threepp::Vector2 general_direction, float burst_radius, int number_of_particles);

    void set_particle_position(std::shared_ptr<threepp::Sprite>& particle_sprite, threepp::Vector2 position);
    std::shared_ptr<BaseController> create_particle_object(std::shared_ptr<threepp::Sprite>& object_sprite, threepp::Vector2 direction);


private:

    threepp::Canvas& canvas_;
    threepp::TextureLoader& loader_;
    std::string material_path_;
    float velocity_;
    float friction_coefficient_ = 0.0f;
    float angle_spread_;
    float scale_;
    float life_time_;

};

#endif//ASTEROIDS_PARTICLE_FACTORY_HPP
