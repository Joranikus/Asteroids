
#include "spaceship_controller.hpp"

using namespace threepp;

SpaceshipController::SpaceshipController(Canvas& canvas,
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

      bullet_factory_(bullet_factory),
      canvas_(canvas){};

//checks each action in an actions set individually, so you can press multiple buttons at the same time
void SpaceshipController::perform_spaceship_movement(const std::set<SpaceshipKeylistener::Action>& actions, float dt) {
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

void SpaceshipController::update(float dt) {
    BaseController::update(dt);
    time_since_last_bullet += dt;
    return_to_screen();
}

void SpaceshipController::on_window_resize(WindowSize& new_screen_size) {
    screen_size_ = new_screen_size;
}

void SpaceshipController::shoot_bullet() {
    if (time_since_last_bullet >= bullet_cooldown_ && ready_to_shoot && !marked_for_removal) {
        bullet_factory_.shoot_bullet(*this);
        ready_to_shoot = false;
    }
}

bool SpaceshipController::out_of_bounds() const {
    if (sprite_->position.x < static_cast<float>(-screen_size_.width) / 2 ||
        sprite_->position.x > static_cast<float>(screen_size_.width) / 2 ||
        sprite_->position.y < static_cast<float>(-screen_size_.height) / 2 ||
        sprite_->position.y > static_cast<float>(screen_size_.height) / 2) {
        return true;
    } else {
        return false;
    }
}

// keeps the spaceship inside the bounds
void SpaceshipController::return_to_screen() {
    if (out_of_bounds()) {
        auto position = get_position();
        auto half_width = static_cast<float>(screen_size_.width) / 2;
        auto half_height = static_cast<float>(screen_size_.height) / 2;

        set_position({
            position.x = std::max(std::min(position.x, half_width), -half_width),
            position.y = std::max(std::min(position.y, half_height), -half_height)
        });
    }
}