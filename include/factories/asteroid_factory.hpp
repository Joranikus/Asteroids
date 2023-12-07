
#ifndef ASTEROIDS_ASTEROID_FACTORY_HPP
#define ASTEROIDS_ASTEROID_FACTORY_HPP

#include "base_factory.hpp"

using namespace threepp;

class AsteroidFactory: public BaseFactory {

public:
    AsteroidFactory(Canvas& canvas,
                    std::shared_ptr<Scene>& scene,
                    TextureLoader& loader,
                    std::vector<std::string> material_paths,
                    float scale,
                    float min_velocity,
                    float max_velocity,
                    float edge_offset);

    void generate_asteroid();
    void generate_wave(float dt, int wave_size, float asteroid_delay, float wave_delay);

    std::shared_ptr<Sprite> create_object_sprite() override;
    std::shared_ptr<BaseController> create_object(std::shared_ptr<Sprite> object_sprite) override;

    void on_window_resize(WindowSize& new_size) override;

private:
    Canvas& canvas_;
    TextureLoader& loader_;
    std::vector<std::string> material_paths_;
    float scale_;
    float min_velocity_;
    float max_velocity_;
    float edge_offset_;

    WindowSize screen_size_ = canvas_.size();

    int asteroids_generated_in_wave = 0;
    float time_since_last_asteroid = 0.0f;
    float time_since_last_wave = 0.0f;
    bool wave_active = false;
};

#endif//ASTEROIDS_ASTEROID_FACTORY_HPP