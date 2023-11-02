
#ifndef ASTEROIDS_SPACESHIP_HPP
#define ASTEROIDS_SPACESHIP_HPP

#include "bullet.hpp"
#include "movement_handler.hpp"
#include "spaceship_keylistener.hpp"
#include "sprite_generator.hpp"
#include "threepp/threepp.hpp"
#include <iostream>

using namespace threepp;

class Spaceship: public PhysicsEngine {

public:
    Spaceship(Sprite& spaceship, float rotation_speed, float thrust_power, float friction_coefficient,
              TextureLoader& bullet_loader, const std::string& bullet_material_path, float bullet_scale, float bullet_speed, WindowSize& screen_size)
        : PhysicsEngine(spaceship, Vector2(0, 1), 0, rotation_speed, thrust_power, friction_coefficient),
          bullet_loader_(bullet_loader), bullet_material_path_(bullet_material_path), bullet_scale_(bullet_scale), bullet_speed_(bullet_speed), screen_size_(screen_size) {}

    //Checks each action in an actions set individually so you can press multiple buttons at the same time
    void perform_spaceship_movement(const std::set<SpaceshipKeylistener::Action>& actions, float dt) {
        for (const auto& action : actions) {
            switch (action) {
                case SpaceshipKeylistener::Action::RotateLeft:
                    rotate_counter_clockwise(dt);
                    break;
                case SpaceshipKeylistener::Action::RotateRight:
                    rotate_clockwise(dt);
                    break;
                case SpaceshipKeylistener::Action::ThrustForward:
                    thrust_forward(dt);
                    break;
                case SpaceshipKeylistener::Action::ThrustBackward:
                    thrust_backward(dt);
                    break;
                case SpaceshipKeylistener::Action::ShootBullet:
                    shoot_bullet(bullet_loader_, bullet_material_path_, bullet_scale_, bullet_speed_);
                    break;
                default:
                    break;
            }
        }
    }

    void update(float dt) override {
        PhysicsEngine::update(dt);
    }

    //creates a shared pointer of sprite_generators,
    void shoot_bullet(TextureLoader& loader, std::string material_path, float scale, float bullet_speed) {

        //creates a bullet sprite and pushes it into a shared pointer
        auto bullet_sprite_generator = std::make_shared<SpriteGenerator>(loader, material_path, scale);
        Sprite& bullet_sprite = *bullet_sprite_generator->get_generated_sprite();

        sprite_generators.push_back(bullet_sprite_generator);

        //adds a velocity and direction to the bullet
        auto new_bullet = std::make_shared<Bullet>(bullet_sprite, get_direction(), bullet_speed);

        //checks if materials are located and sets the bullet rotation to the spaceship rotation
        auto spaceship_material = this->sprite_.material;
        if (spaceship_material) {
            auto bullet_material = bullet_sprite.material;
            if (bullet_material) {
                bullet_material->rotation = spaceship_material->rotation;
            }
        }

        //offsets the bullet in accordance to the spaceship
        float bullet_front_offset = this->sprite_.scale.x * 0.5;
        Vector2 offset_position = {
                this->sprite_.position.x + get_direction().x * bullet_front_offset,
                this->sprite_.position.y + get_direction().y * bullet_front_offset
        };
        bullet_sprite.position.set(offset_position.x, offset_position.y, 0);

        bullets.push_back(new_bullet);
    }

    void on_window_resize(WindowSize& screen_size) {
        screen_size_ = screen_size;
    }

    //denne funksjonen er skrevet med hjelp fra ChatGPT
    //deletes bullet when out of bounds
    void update_bullets(float dt, std::shared_ptr<Scene> scene) {
        for (auto i = bullets.begin(); i != bullets.end();) {
            auto& bullet = *i;
            bullet->update(dt);

        if (bullet->get_sprite().position.x < -screen_size_.width / 2 ||
            bullet->get_sprite().position.x > screen_size_.width / 2 ||
            bullet->get_sprite().position.y < -screen_size_.height / 2 ||
            bullet->get_sprite().position.y > screen_size_.height / 2) {

            scene->remove(bullet->get_sprite());

            i = bullets.erase(i);
        } else {
            ++i;
        }
        }
    }

    const std::vector<std::shared_ptr<Bullet>>& get_bullets() {
        return bullets;
    }

private:

    void rotate_counter_clockwise(float dt) override {
        PhysicsEngine::rotate_counter_clockwise(dt);
    }

    void rotate_clockwise(float dt) override {
        PhysicsEngine::rotate_clockwise(dt);
    }

    void thrust_forward(float dt) override {
        PhysicsEngine::thrust_forward(dt);
    }

    void thrust_backward(float dt) override {
        PhysicsEngine::thrust_backward(dt);
    }

    std::vector<std::shared_ptr<Bullet>> bullets;
    std::vector<std::shared_ptr<SpriteGenerator>> sprite_generators;
    TextureLoader& bullet_loader_;
    std::string bullet_material_path_;
    float bullet_scale_;
    float bullet_speed_;
    WindowSize& screen_size_;


};

#endif//ASTEROIDS_SPACESHIP_HPP