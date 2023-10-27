
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
        None
    };

    Action determine_action(const SpaceshipKeylistener& keylistener) {
        if (keylistener.isKeyPressed(Key::LEFT)) return Action::RotateLeft;
        if (keylistener.isKeyPressed(Key::RIGHT)) return Action::RotateRight;
        if (keylistener.isKeyPressed(Key::UP)) return Action::ThrustForward;
        if (keylistener.isKeyPressed(Key::DOWN)) return Action::ThrustBackward;
        return Action::None;
    }

};

#endif//ASTEROIDS_SPACESHIP_CONTROLLER_HPP
