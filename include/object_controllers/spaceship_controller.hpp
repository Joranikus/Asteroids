
#ifndef ASTEROIDS_SPACESHIP_CONTROLLER_HPP
#define ASTEROIDS_SPACESHIP_CONTROLLER_HPP

#include "functions/create_sprite.hpp"
#include "object_controllers/bullet_controller.hpp"
#include "object_controllers/object_controller.hpp"
#include "spaceship_keylistener.hpp"
#include "threepp/threepp.hpp"
#include <iostream>

using namespace threepp;

class SpaceshipController: public ObjectController {

public:
    SpaceshipController(std::shared_ptr<Sprite> spaceship, WindowSize& screen_size, float spaceship_rotation_speed, float spaceship_thrust_power, float friction_coefficient,
              TextureLoader& bullet_loader, const std::string& bullet_material_path, float bullet_scale, float bullet_velocity, float bullet_cooldown)
        : ObjectController(spaceship, Vector2(0, 1), 0, spaceship_rotation_speed, spaceship_thrust_power, friction_coefficient),
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
        ObjectController::update(dt);
        time_since_last_bullet += dt;
    }

    void on_window_resize(WindowSize& screen_size) {
        screen_size_ = screen_size;
    }

    //denne funksjonen er skrevet med hjelp fra ChatGPT
    //updates and deletes bullet when out of bounds
    /*
    void update_bullets(float dt, const std::shared_ptr<Scene>& scene) {
        for (auto i = bullets.begin(); i != bullets.end();) {
            auto& bullet = *i;
            bullet->update(dt);

             auto bullet_sprite = bullet->get_sprite();
            if (bullet->get_sprite()->position.x < -screen_size_.width / 2 ||
                bullet->get_sprite()->position.x > screen_size_.width / 2 ||
                bullet->get_sprite()->position.y < -screen_size_.height / 2 ||
                bullet->get_sprite()->position.y > screen_size_.height / 2) {

                scene->remove(*bullet_sprite);

                i = bullets.erase(i);
            } else {
                ++i;
            }
        }
    }
    */
    //denne delen for å slette asteroider og sprites er laget med hjelp fra ChatGPT
    void update_bullets(float dt, const std::shared_ptr<Scene>& scene) {
        std::vector<int> to_remove;

        for (size_t index = 0; index < bullets.size(); ++index) {
            auto& bullet = bullets[index];
            bullet->update(dt);

            auto bullet_sprite = bullet->get_sprite();
            if (bullet_sprite->position.x < -screen_size_.width / 2 ||
                bullet_sprite->position.x > screen_size_.width / 2 ||
                bullet_sprite->position.y < -screen_size_.height / 2 ||
                bullet_sprite->position.y > screen_size_.height / 2) {

                to_remove.push_back(index);
            }
        }

        for (auto it = to_remove.rbegin(); it != to_remove.rend(); ++it) {
            int index = *it;
            scene->remove(*bullet_sprites[index]);
            bullets.erase(bullets.begin() + index);
            bullet_sprites.erase(bullet_sprites.begin() + index);
        }
    }

    const std::vector<std::shared_ptr<BulletController>>& get_bullets() {
        return bullets;
    }

private:

    void shoot_bullet() {

        if (time_since_last_bullet >= bullet_cooldown_ && ready_to_shoot) {

            //creates a bullet sprite and pushes it into a shared pointer
            auto bullet_sprite = create_sprite(bullet_loader_, bullet_material_path_, bullet_scale_);
            bullet_sprites.push_back(bullet_sprite);

            //adds a velocity and direction to the bullet
            auto bullet = std::make_shared<BulletController>(bullet_sprite, get_direction(), bullet_velocity_);

            //checks if materials are located and sets the bullet rotation to the spaceship rotation
            auto spaceship_material = this->get_sprite()->material;
            if (spaceship_material) {
                auto bullet_material = bullet_sprite->material;
                if (bullet_material) {
                    bullet_material->rotation = spaceship_material->rotation;
                }
            }

            //offsets the bullet in accordance to the spaceship
            float bullet_front_offset = this->get_sprite()->scale.x * 0.3;
            Vector2 offset_position = {
                    this->get_sprite()->position.x + get_direction().x * bullet_front_offset,
                    this->get_sprite()->position.y + get_direction().y * bullet_front_offset
            };
            bullet_sprite->position.set(offset_position.x, offset_position.y, 0);

            bullets.push_back(bullet);

            time_since_last_bullet = 0.0f;
            ready_to_shoot = false;

            std::cout << "Bullet count after addition: " << bullets.size() << std::endl;
            std::cout << "Bullet sprites count after addition: " << bullet_sprites.size() << std::endl;
        }
    }

    void rotate_counter_clockwise(float dt) override {
        ObjectController::rotate_counter_clockwise(dt);
    }

    void rotate_clockwise(float dt) override {
        ObjectController::rotate_clockwise(dt);
    }

    void thrust_forward(float dt) override {
        ObjectController::thrust_forward(dt);
    }

    void thrust_backward(float dt) override {
        ObjectController::thrust_backward(dt);
    }

    std::vector<std::shared_ptr<BulletController>> bullets;
    std::vector<std::shared_ptr<Sprite>> bullet_sprites;
    TextureLoader& bullet_loader_;
    std::string bullet_material_path_;
    float bullet_scale_;
    float bullet_velocity_;
    float bullet_cooldown_;
    float time_since_last_bullet = 0.0f;
    bool ready_to_shoot;
    WindowSize& screen_size_;

};

#endif//ASTEROIDS_SPACESHIP_CONTROLLER_HPP