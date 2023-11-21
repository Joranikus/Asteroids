
#ifndef ASTEROIDS_SPACESHIP_CONTROLLER_HPP
#define ASTEROIDS_SPACESHIP_CONTROLLER_HPP

#include "factories/bullet_factory.hpp"
#include "spaceship_keylistener.hpp"
#include "threepp/threepp.hpp"

using namespace threepp;

class SpaceshipController: public BaseController {

public:
    SpaceshipController(Canvas& canvas,
                        BulletFactory& bullet_factory,
                        std::shared_ptr<Sprite>& spaceship,
                        float spaceship_rotation_speed,
                        float spaceship_thrust_power,
                        float friction_coefficient)

        : BaseController(spaceship,
                         Vector2(0, 1),
                         spaceship_rotation_speed,
                         friction_coefficient,
                         spaceship_thrust_power),

          bullet_factory_(bullet_factory) {};

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
        BaseController::update(dt);
        time_since_last_bullet += dt;
    }

private:

    void shoot_bullet() {
        if (time_since_last_bullet >= bullet_cooldown_ && ready_to_shoot) {
            bullet_factory_.shoot_bullet(*this);
            ready_to_shoot = false;
        }
    }

    float bullet_cooldown_{};
    float time_since_last_bullet = 0.0f;
    bool ready_to_shoot{};
    BulletFactory& bullet_factory_;
};

#endif//ASTEROIDS_SPACESHIP_CONTROLLER_HPP