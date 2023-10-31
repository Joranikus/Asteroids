
#ifndef ASTEROIDS_SPACESHIP_CONTROLLER_HPP
#define ASTEROIDS_SPACESHIP_CONTROLLER_HPP

#include "spaceship_keylistener.hpp"

class SpaceshipController {

public:

    //Fikk inspirasjon fra ChatGPT om enum class
    enum class Action {
        RotateLeft,
        RotateRight,
        ThrustForward,
        ThrustBackward,
        ShootBullet,
    };

    //Puts all the active actions in a actions set
    std::set<Action> determine_action(const SpaceshipKeylistener& keylistener) {
        std::set<Action> actions;
        if (keylistener.isKeyPressed(Key::LEFT) or keylistener.isKeyPressed(Key::A)) actions.insert(Action::RotateLeft);
        if (keylistener.isKeyPressed(Key::RIGHT) or keylistener.isKeyPressed(Key::D)) actions.insert(Action::RotateRight);
        if (keylistener.isKeyPressed(Key::UP) or keylistener.isKeyPressed(Key::W)) actions.insert(Action::ThrustForward);
        if (keylistener.isKeyPressed(Key::DOWN) or keylistener.isKeyPressed(Key::S)) actions.insert(Action::ThrustBackward);
        if (keylistener.isKeyPressed(Key::SPACE)) actions.insert(Action::ShootBullet);
        return actions;
    }

};

#endif//ASTEROIDS_SPACESHIP_CONTROLLER_HPP
