
#ifndef ASTEROIDS_SPACESHIP_KEYLISTENER_HPP
#define ASTEROIDS_SPACESHIP_KEYLISTENER_HPP

#include "threepp/threepp.hpp"
#include <set>

using namespace threepp;

//inserts and erases keys from a set so multiple keys can be pressed at the same time
class SpaceshipKeylistener : public KeyListener {
public:

    void onKeyPressed(KeyEvent evt) override {
        keys_pressed.insert(evt.key);
    }

    void onKeyReleased(KeyEvent evt) override {
        keys_pressed.erase(evt.key);
    }

    bool isKeyPressed(Key key) const {
        return keys_pressed.find(key) != keys_pressed.end();
    }

    enum class Action {
        RotateLeft,
        RotateRight,
        ThrustForward,
        ThrustBackward,
        ShootBullet,
    };

    std::set<Action> determine_action() const {
        std::set<Action> actions;
        if (this->isKeyPressed(Key::A)) actions.insert(Action::RotateLeft);
        if (this->isKeyPressed(Key::D)) actions.insert(Action::RotateRight);
        if (this->isKeyPressed(Key::W)) actions.insert(Action::ThrustForward);
        if (this->isKeyPressed(Key::S)) actions.insert(Action::ThrustBackward);
        if (this->isKeyPressed(Key::SPACE)) actions.insert(Action::ShootBullet);
        return actions;
    }

private:

    //Fikk inspirasjon av ChatGPT om å lage et set
    std::set<Key> keys_pressed;
};
#endif//ASTEROIDS_SPACESHIP_KEYLISTENER_HPP
