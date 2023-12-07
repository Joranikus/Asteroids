
#ifndef ASTEROIDS_SPACESHIP_CONTROLLER_HPP
#define ASTEROIDS_SPACESHIP_CONTROLLER_HPP

#include "factories/bullet_factory.hpp"
#include "keylisteners/spaceship_keylistener.hpp"
#include "threepp/threepp.hpp"

class SpaceshipController: public BaseController {

public:
    SpaceshipController(threepp::Canvas& canvas,
                        BulletFactory& bullet_factory,
                        std::shared_ptr<threepp::Sprite>& spaceship,
                        float spaceship_rotation_speed,
                        float spaceship_thrust_power,
                        float friction_coefficient);

    void perform_spaceship_movement(const std::set<SpaceshipKeylistener::Action>& actions, float dt);
    void update(float dt) override;

private:
    void shoot_bullet();

    float bullet_cooldown_{};
    float time_since_last_bullet = 0.0f;
    bool ready_to_shoot{};
    BulletFactory& bullet_factory_;
};

#endif//ASTEROIDS_SPACESHIP_CONTROLLER_HPP