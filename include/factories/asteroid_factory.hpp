

#ifndef ASTEROIDS_ASTEROID_FACTORY_HPP
#define ASTEROIDS_ASTEROID_FACTORY_HPP

#include "base_factory.hpp"
#include "functions/create_sprite.hpp"
#include "functions/random_functions.hpp"
#include "object_controllers/asteroid_controller.hpp"
#include "threepp/threepp.hpp"

using namespace threepp;

class AsteroidFactory : public BaseFactory {

public:

    AsteroidFactory(Canvas& canvas, std::shared_ptr<Scene>& scene, TextureLoader& loader, std::string material_path, float scale,
                    float min_velocity, float max_velocity, float edge_offset)
    : BaseFactory(canvas, scene, loader, material_path, scale, edge_offset),
          canvas_(canvas), edge_offset_(edge_offset),min_velocity_(min_velocity), max_velocity_(max_velocity) {}

    void generate_asteroid() {
        auto asteroid_sprite = create_object_sprite();
        auto asteroid = create_object(asteroid_sprite);
        add_to_scene(asteroid_sprite);

        std::cout << "Asteroids count after addition: " << objects.size() << std::endl;
        std::cout << "Asteroid sprite count after addition: " << object_sprites.size() << std::endl;
    }

    void generate_wave(float dt, int wave_size, float asteroid_delay) {
        time_since_last_asteroid += dt;

        if (time_since_last_asteroid >= asteroid_delay && objects.size() < wave_size) {
            generate_asteroid();
            time_since_last_asteroid = 0.0f;
        }
    }

    std::shared_ptr<BaseController> create_object(std::shared_ptr<Sprite> object_sprite) override {
        auto asteroid = std::make_shared<AsteroidController>(object_sprite, screen_size_,random_direction(),
                                                             edge_offset_, min_velocity_, max_velocity_);
        objects.push_back(asteroid);
        return asteroid;
    }

private:

    Canvas& canvas_;
    float edge_offset_;
    WindowSize screen_size_ = canvas_.size();

    float min_velocity_;
    float max_velocity_;

    float time_since_last_asteroid = 0.0f;

};

#endif//ASTEROIDS_ASTEROID_FACTORY_HPP
