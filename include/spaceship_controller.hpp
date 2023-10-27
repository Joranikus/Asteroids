
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
    };

    //Puts all the active actions in a actions set
    std::set<Action> determine_action(const SpaceshipKeylistener& keylistener) {
        std::set<Action> actions;
        if (keylistener.isKeyPressed(Key::LEFT)) actions.insert(Action::RotateLeft);
        if (keylistener.isKeyPressed(Key::RIGHT)) actions.insert(Action::RotateRight);
        if (keylistener.isKeyPressed(Key::UP)) actions.insert(Action::ThrustForward);
        if (keylistener.isKeyPressed(Key::DOWN)) actions.insert(Action::ThrustBackward);
        return actions;
    }

};

#endif//ASTEROIDS_SPACESHIP_CONTROLLER_HPP
