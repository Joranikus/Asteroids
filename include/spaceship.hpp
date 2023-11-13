
#ifndef ASTEROIDS_SPACESHIP_HPP
#define ASTEROIDS_SPACESHIP_HPP

#include "bullet.hpp"
#include "movement_handler.hpp"
#include "spaceship_keylistener.hpp"
#include "sprite_generator.hpp"
#include "threepp/threepp.hpp"
#include <iostream>

using namespace threepp;

class Spaceship: public MovementHandler {

public:
    Spaceship(Sprite& spaceship, WindowSize& screen_size, float spaceship_rotation_speed, float spaceship_thrust_power, float friction_coefficient,
              TextureLoader& bullet_loader, const std::string& bullet_material_path, float bullet_scale, float bullet_velocity, float bullet_cooldown)
        : MovementHandler(spaceship, Vector2(0, 1), 0, spaceship_rotation_speed, spaceship_thrust_power, friction_coefficient),
          screen_size_(screen_size), bullet_loader_(bullet_loader), bullet_material_path_(bullet_material_path), bullet_scale_(bullet_scale), bullet_velocity_(bullet_velocity), bullet_cooldown_(bullet_cooldown)  {}

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
                    shoot_bullet();
                    break;
                case SpaceshipKeylistener::Action::BulletFlagReset:
                    ready_to_shoot = true;
                    break;
                default:
                    break;
            }
        }
    }

    void update(float dt) override {
        MovementHandler::update(dt);
        time_since_last_bullet += dt;
    }

    //creates a shared pointer of sprite_generators,


    void on_window_resize(WindowSize& screen_size) {
        screen_size_ = screen_size;
    }

    //denne funksjonen er skrevet med hjelp fra ChatGPT
    //updates and deletes bullet when out of bounds
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

    void shoot_bullet() {

        if (time_since_last_bullet >= bullet_cooldown_ && ready_to_shoot) {

            //creates a bullet sprite and pushes it into a shared pointer
            auto bullet_sprite = std::make_shared<SpriteGenerator>(bullet_loader_, bullet_material_path_, bullet_scale_);
            Sprite& bullet = *bullet_sprite->get_generated_sprite();

            sprite_generators.push_back(bullet_sprite);

            //adds a velocity and direction to the bullet
            auto new_bullet = std::make_shared<Bullet>(bullet, get_direction(), bullet_velocity_);

            //checks if materials are located and sets the bullet rotation to the spaceship rotation
            auto spaceship_material = this->object_.material;
            if (spaceship_material) {
                auto bullet_material = bullet.material;
                if (bullet_material) {
                    bullet_material->rotation = spaceship_material->rotation;
                }
            }

            //offsets the bullet in accordance to the spaceship
            float bullet_front_offset = this->object_.scale.x * 0.3;
            Vector2 offset_position = {
                    this->object_.position.x + get_direction().x * bullet_front_offset,
                    this->object_.position.y + get_direction().y * bullet_front_offset
            };
            bullet.position.set(offset_position.x, offset_position.y, 0);

            bullets.push_back(new_bullet);

            time_since_last_bullet = 0.0f;
            ready_to_shoot = false;
        }
    }

    void rotate_counter_clockwise(float dt) override {
        MovementHandler::rotate_counter_clockwise(dt);
    }

    void rotate_clockwise(float dt) override {
        MovementHandler::rotate_clockwise(dt);
    }

    void thrust_forward(float dt) override {
        MovementHandler::thrust_forward(dt);
    }

    void thrust_backward(float dt) override {
        MovementHandler::thrust_backward(dt);
    }

    std::vector<std::shared_ptr<Bullet>> bullets;
    std::vector<std::shared_ptr<SpriteGenerator>> sprite_generators;
    TextureLoader& bullet_loader_;
    std::string bullet_material_path_;
    float bullet_scale_;
    float bullet_velocity_;
    float bullet_cooldown_;
    float time_since_last_bullet;
    bool ready_to_shoot;
    WindowSize& screen_size_;

};

#endif//ASTEROIDS_SPACESHIP_HPP