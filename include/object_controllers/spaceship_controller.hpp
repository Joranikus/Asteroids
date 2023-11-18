
#ifndef ASTEROIDS_SPACESHIP_CONTROLLER_HPP
#define ASTEROIDS_SPACESHIP_CONTROLLER_HPP

#include "functions/create_sprite.hpp"
#include "object_controllers/bullet_controller.hpp"
#include "object_controllers/object_controller.hpp"
#include "spaceship_keylistener.hpp"
#include "threepp/threepp.hpp"
#include <iostream>
#include "factories/bullet_factory.hpp"

using namespace threepp;

class SpaceshipController: public ObjectController {

public:
    SpaceshipController(Canvas& canvas, BulletFactory& bullet_factory, std::shared_ptr<Sprite>& spaceship, float spaceship_rotation_speed,
                        float spaceship_thrust_power, float friction_coefficient)

        : ObjectController(spaceship, Vector2(0, 1), 0, spaceship_rotation_speed,
                           spaceship_thrust_power, friction_coefficient), canvas_(canvas), bullet_factory_(bullet_factory) {};

    //checks each action in an actions set individually so you can press multiple buttons at the same time
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

private:

    void shoot_bullet() {
        if (time_since_last_bullet >= bullet_cooldown_ && ready_to_shoot) {
            bullet_factory_.shoot_bullet(*this);
            ready_to_shoot = false;
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

    float bullet_cooldown_{};
    float time_since_last_bullet = 0.0f;
    bool ready_to_shoot{};
    Canvas& canvas_;
    BulletFactory& bullet_factory_;
    WindowSize screen_size_ = canvas_.size();

};

#endif//ASTEROIDS_SPACESHIP_CONTROLLER_HPP