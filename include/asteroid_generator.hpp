

#ifndef ASTEROIDS_ASTEROID_GENERATOR_HPP
#define ASTEROIDS_ASTEROID_GENERATOR_HPP

#include "object_controllers/asteroid_controller.hpp"
#include "functions/create_sprite.hpp"
#include "threepp/threepp.hpp"

using namespace threepp;

class AsteroidGenerator {

public:

    AsteroidGenerator(WindowSize& screen_size, TextureLoader& loader, std::string& material_path, float scale,
                      float edge_offset, float min_velocity, float max_velocity)
                      : screen_size_(screen_size), loader_(loader), material_path_(material_path), scale_(scale),
                        edge_offset_(edge_offset), min_velocity_(min_velocity), max_velocity_(max_velocity) {}

    const std::vector<std::shared_ptr<AsteroidController>>& get_asteroids() {
        return asteroids;
    }

    void update_asteroids(float dt, const std::shared_ptr<Scene>& scene) {
        for (auto i = asteroids.begin(); i != asteroids.end();) {
            auto& asteroid = *i;
            asteroid->update(dt);

            auto asteroid_sprite = asteroid->get_sprite();
            if (asteroid->get_sprite()->position.x < -screen_size_.width / 2 - edge_offset_ ||
                asteroid->get_sprite()->position.x > screen_size_.width / 2 + edge_offset_ ||
                asteroid->get_sprite()->position.y < -screen_size_.height / 2 - edge_offset_ ||
                asteroid->get_sprite()->position.y > screen_size_.height / 2 + edge_offset_) {

                scene->remove(*asteroid_sprite);

                i = asteroids.erase(i);
            } else {
                ++i;
            }
        }
    }

private:

    void generate_asteroid() {
        auto asteroid_sprite = create_sprite(loader_, material_path_, scale_);
        asteroid_sprites.push_back(asteroid_sprite);

        auto asteroid = std::make_shared<AsteroidController>(asteroid_sprite, screen_size_, edge_offset_, min_velocity_, max_velocity_);
        asteroids.push_back(asteroid);
    }

    std::vector<std::shared_ptr<AsteroidController>> asteroids;
    std::vector<std::shared_ptr<Sprite>> asteroid_sprites;

    WindowSize& screen_size_;
    TextureLoader& loader_;
    std::string material_path_;
    float scale_;
    float edge_offset_;
    float min_velocity_;
    float max_velocity_;

};

#endif//ASTEROIDS_ASTEROID_GENERATOR_HPP
