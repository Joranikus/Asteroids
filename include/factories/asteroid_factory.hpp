
#ifndef ASTEROIDS_ASTEROID_FACTORY_HPP
#define ASTEROIDS_ASTEROID_FACTORY_HPP

#include "base_factory.hpp"
#include "functions/random_functions.hpp"
#include "threepp/threepp.hpp"

class AsteroidFactory : public BaseFactory {

public:
    AsteroidFactory(threepp::Canvas& canvas,
                    std::shared_ptr<threepp::Scene>& scene,
                    threepp::TextureLoader& loader,
                    std::vector<std::string> material_paths,
                    float scale,
                    float min_velocity,
                    float max_velocity,
                    float edge_offset);

    void generate_asteroid();
    void generate_wave(float dt, int wave_size, float asteroid_delay, float wave_delay);

    std::shared_ptr<threepp::Sprite> create_object_sprite() override;
    std::shared_ptr<BaseController> create_object(std::shared_ptr<threepp::Sprite> object_sprite) override;

    //TODO: korfor må jeg gjøre dette i det hele tatt? funksjonen er jo i base klassen.
    void on_window_resize(threepp::WindowSize& new_size) override;

private:

    threepp::Canvas& canvas_;
    threepp::TextureLoader& loader_;
    std::vector<std::string> material_paths_;
    float scale_;
    float min_velocity_;
    float max_velocity_;
    float edge_offset_;

    threepp::WindowSize screen_size_ = canvas_.size();

    int asteroids_generated_in_wave = 0;
    float time_since_last_asteroid = 0.0f;
    float time_since_last_wave = 0.0f;
    bool wave_active = false;

};

#endif//ASTEROIDS_ASTEROID_FACTORY_HPP