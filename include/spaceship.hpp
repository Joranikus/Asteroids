
#ifndef ASTEROIDS_SPACESHIP_HPP
#define ASTEROIDS_SPACESHIP_HPP

#include "physics_handler.hpp"
#include "spaceship_keylistener.hpp"
#include "sprite_generator.hpp"
#include "threepp/threepp.hpp"
#include "bullet.hpp"
#include <iostream>

using namespace threepp;

class Spaceship: public PhysicsEngine {

public:
    Spaceship(Sprite& spaceship, float rotation_speed, float thrust_power, float friction_coefficient,
              TextureLoader& bullet_loader, const std::string& bullet_material_path, float bullet_scale, float bullet_speed)
        : PhysicsEngine(spaceship, Vector2(0, 1), 0, rotation_speed, thrust_power, friction_coefficient),
          bullet_loader_(bullet_loader), bullet_material_path_(bullet_material_path), bullet_scale_(bullet_scale), bullet_speed_(bullet_speed) {}

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

        auto bullet_sprite_generator = std::make_shared<SpriteGenerator>(loader, material_path, scale);
        Sprite& bulletSprite = *bullet_sprite_generator->get_generated_sprite();

        sprite_generators.push_back(bullet_sprite_generator);

        Vector2 direction = get_direction();

        auto new_bullet = std::make_shared<Bullet>(bulletSprite, direction, bullet_speed);

        bullets.push_back(new_bullet);
        // TODO: DELETE BULLETS
        // TODO: USE POSITION VECTOR TO SO BULLETS SHOOT FROM SPACESHIP
        // TODO: ROTATE BULLET MATERIAL
    }

    void update_bullets(float dt) {
        for (auto& bullet : bullets) {
            bullet->update(dt);
        }
    }

    const std::vector<std::shared_ptr<Bullet>>& get_bullets() const {
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


};

#endif//ASTEROIDS_SPACESHIP_HPP