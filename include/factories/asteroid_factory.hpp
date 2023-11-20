
#ifndef ASTEROIDS_ASTEROID_FACTORY_HPP
#define ASTEROIDS_ASTEROID_FACTORY_HPP

#include "base_factory.hpp"
#include "functions/create_sprite.hpp"
#include "functions/random_functions.hpp"
#include "controllers/asteroid_controller.hpp"
#include "threepp/threepp.hpp"

using namespace threepp;

class AsteroidFactory : public BaseFactory {

public:

    AsteroidFactory(Canvas& canvas, std::shared_ptr<Scene>& scene, TextureLoader& loader, std::vector<std::string> material_paths, float scale,
                    float min_velocity, float max_velocity, float edge_offset)
    : BaseFactory(canvas, scene, loader, std::string(""), scale, edge_offset),
          canvas_(canvas), loader_(loader), material_paths_(material_paths), scale_(scale), edge_offset_(edge_offset),min_velocity_(min_velocity), max_velocity_(max_velocity) {}

    void generate_asteroid() {
        auto asteroid_sprite = create_object_sprite();
        auto asteroid = create_object(asteroid_sprite);
        add_to_scene(asteroid_sprite);
    }

    void generate_wave(float dt, int wave_size, float asteroid_delay, float wave_delay) {
        // increment the timers
        time_since_last_asteroid += dt;

        // ceck if the wave is active and if all asteroids from the wave have been destroyed
        if (wave_active && objects.empty()) {
            wave_active = false;
            time_since_last_wave = 0.0f; // Reset the wave timer since the wave has ended
        }

        // if the wave is not active, increment the wave timer
        if (!wave_active) {
            time_since_last_wave += dt;
        }

        // starts a new wave if the previous wave has ended and the delay has passed
        if (!wave_active && time_since_last_wave >= wave_delay) {
            wave_active = true;
            asteroids_generated_in_wave = 0;
            time_since_last_asteroid = asteroid_delay;
        }

        // generates asteroids for the active wave
        if (wave_active && time_since_last_asteroid >= asteroid_delay && asteroids_generated_in_wave < wave_size) {
            generate_asteroid();
            asteroids_generated_in_wave++;
            time_since_last_asteroid = 0.0f;
        }
    }

    std::shared_ptr<Sprite> create_object_sprite() override {
        int random_material = random_int(0, material_paths_.size() - 1);
        std::string image = material_paths_[random_material];

        auto object_sprite = create_sprite(loader_, image , scale_);
        object_sprites.push_back(object_sprite);
        return object_sprite;
    }

    std::shared_ptr<BaseController> create_object(std::shared_ptr<Sprite> object_sprite) override {
        auto asteroid = std::make_shared<AsteroidController>(object_sprite, screen_size_,random_direction(), 0,
                                                             edge_offset_, min_velocity_, max_velocity_);
        asteroid->set_initial_rotation(random_rotation_speed());

        objects.push_back(asteroid);
        return asteroid;
    }

    float random_rotation_speed() {
        return random_float(-10, 10);
    }

    //TODO: korfor må jeg gjøre dette i det hele tatt? funksjonen er jo i base klassen.
    void on_window_resize(WindowSize& new_size) override {
        BaseFactory::on_window_resize(new_size);
        screen_size_ = new_size;
    }

private:


    float edge_offset_;
    Canvas& canvas_;
    TextureLoader& loader_;
    std::vector<std::string> material_paths_;
    float scale_;
    WindowSize screen_size_ = canvas_.size();
    float min_velocity_;
    float max_velocity_;

    int asteroids_generated_in_wave = 0;
    float time_since_last_asteroid = 0.0f;
    float time_since_last_wave = 0.0f;
    bool wave_active = false;

};

#endif//ASTEROIDS_ASTEROID_FACTORY_HPP
