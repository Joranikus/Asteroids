

#ifndef ASTEROIDS_ASTEROID_FACTORY_HPP
#define ASTEROIDS_ASTEROID_FACTORY_HPP

#include "object_controllers/asteroid_controller.hpp"
#include "functions/create_sprite.hpp"
#include "functions/random_functions.hpp"
#include "threepp/threepp.hpp"

using namespace threepp;

class AsteroidFactory {

public:
    AsteroidFactory(WindowSize& screen_size, TextureLoader& loader, std::string material_path, float scale,
                      float edge_offset, float min_velocity, float max_velocity)
                      : screen_size_(screen_size), loader_(loader), material_path_(material_path), scale_(scale),
                        edge_offset_(edge_offset), min_velocity_(min_velocity), max_velocity_(max_velocity) {}

    const std::vector<std::shared_ptr<AsteroidController>>& get_asteroids() {
        return asteroids;
    }

    //denne delen for å slette asteroider og sprites er laget med hjelp fra ChatGPT
    void update_asteroids(float dt, const std::shared_ptr<Scene>& scene) {
        std::vector<int> to_remove;

        for (size_t index = 0; index < asteroids.size(); ++index) {
            auto& asteroid = asteroids[index];
            asteroid->update(dt);

            auto asteroid_sprite = asteroid->get_sprite();
            if (asteroid_sprite->position.x < -screen_size_.width / 2 - edge_offset_ ||
                asteroid_sprite->position.x > screen_size_.width / 2 + edge_offset_ ||
                asteroid_sprite->position.y < -screen_size_.height / 2 - edge_offset_ ||
                asteroid_sprite->position.y > screen_size_.height / 2 + edge_offset_) {

                to_remove.push_back(index);
            }
        }

        for (auto it = to_remove.rbegin(); it != to_remove.rend(); ++it) {
            int index = *it;
            scene->remove(*asteroid_sprites[index]);
            asteroids.erase(asteroids.begin() + index);
            asteroid_sprites.erase(asteroid_sprites.begin() + index);
        }
    }

    void generate_asteroid(std::shared_ptr<Scene>& scene) {
        auto asteroid_sprite = create_sprite(loader_, material_path_, scale_);
        asteroid_sprites.push_back(asteroid_sprite);

        auto asteroid = std::make_shared<AsteroidController>(asteroid_sprite, screen_size_, random_direction(),
                                                             edge_offset_, min_velocity_, max_velocity_);
        asteroids.push_back(asteroid);

        scene->add(asteroid_sprite);

        std::cout << "Asteroids count after addition: " << asteroids.size() << std::endl;
        std::cout << "Asteroid sprites count after addition: " << asteroid_sprites.size() << std::endl;
    }

    void generate_wave(std::shared_ptr<Scene>& scene, float dt, int wave_size, float asteroid_delay) {
        time_since_last_asteroid += dt;

        if (time_since_last_asteroid >= asteroid_delay && asteroids.size() < wave_size) {
            generate_asteroid(scene);
            time_since_last_asteroid = 0.0f;
        }
    }

private:

    std::vector<std::shared_ptr<AsteroidController>> asteroids;
    std::vector<std::shared_ptr<Sprite>> asteroid_sprites;
    float time_since_last_asteroid = 0.0f;

    WindowSize& screen_size_;
    TextureLoader& loader_;
    std::string material_path_;
    float scale_;
    float edge_offset_;
    float min_velocity_;
    float max_velocity_;

};

#endif//ASTEROIDS_ASTEROID_FACTORY_HPP
