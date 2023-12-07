
#include "asteroid_factory.hpp"
#include "functions/create_sprite.hpp"
#include "functions/random_functions.hpp"

#include "controllers/asteroid_controller.hpp"

using namespace threepp;

AsteroidFactory::AsteroidFactory(Canvas& canvas,
                                 std::shared_ptr<Scene>& scene,
                                 TextureLoader& loader,
                                 std::vector<std::string> material_paths,
                                 float scale,
                                 float min_velocity,
                                 float max_velocity,
                                 float edge_offset)

    : BaseFactory(canvas,
                  scene,
                  loader,
                  std::string(""),
                  scale,
                  edge_offset),

      canvas_(canvas),
      loader_(loader),
      material_paths_(std::move(material_paths)),
      scale_(scale),
      min_velocity_(min_velocity),
      max_velocity_(max_velocity),
      edge_offset_(edge_offset) {}

void AsteroidFactory::generate_asteroid() {
    auto asteroid_sprite = create_object_sprite();
    auto asteroid = create_object(asteroid_sprite);
    add_to_scene(asteroid_sprite);
}

void AsteroidFactory::generate_wave(float dt, const int wave_size, const float asteroid_delay, const float wave_delay) {
    // increment the timers
    time_since_last_asteroid += dt;

    // ceck if the wave is active and if all asteroids from the wave have been destroyed
    if (wave_active && objects.empty()) {
        wave_active = false;
        time_since_last_wave = 0.0f;// Reset the wave timer since the wave has ended
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

std::shared_ptr<Sprite> AsteroidFactory::create_object_sprite() {
    int random_material = random_int(0, material_paths_.size() - 1);
    std::string image = material_paths_[random_material];

    auto object_sprite = create_sprite(loader_, image, scale_);
    object_sprites.emplace_back(object_sprite);
    return object_sprite;
}

std::shared_ptr<BaseController> AsteroidFactory::create_object(std::shared_ptr<Sprite> object_sprite) {
    float random_rotation_speed = random_float(-7, 7);
    auto asteroid = std::make_shared<AsteroidController>(object_sprite,
                                                         screen_size_,
                                                         random_direction(),
                                                         random_rotation_speed,
                                                         min_velocity_,
                                                         max_velocity_,
                                                         edge_offset_);
    objects.emplace_back(asteroid);
    return asteroid;
}

//TODO: korfor må jeg gjøre dette i det hele tatt? funksjonen er jo i base klassen.
void AsteroidFactory::on_window_resize(WindowSize& new_size) {
    BaseFactory::on_window_resize(new_size);
    screen_size_ = new_size;
}