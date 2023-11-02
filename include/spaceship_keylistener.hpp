
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
        keys_released.erase(evt.key);
    }

    void onKeyReleased(KeyEvent evt) override {
        keys_pressed.erase(evt.key);
        keys_released.insert(evt.key);
    }

    bool isKeyPressed(Key key) const {
        return keys_pressed.find(key) != keys_pressed.end();
    }

    bool isKeyReleased(Key key) const {
        return keys_released.find(key) != keys_released.end();
    }

    //fikk inspirasjon fra chat gpt til å lage en enum class
    enum class Action {
        RotateLeft,
        RotateRight,
        ThrustForward,
        ThrustBackward,
        ShootBullet,
        BulletFlagReset,
    };

    std::set<Action> determine_action() {
        std::set<Action> actions;
        if (this->isKeyPressed(Key::A)) actions.insert(Action::RotateLeft);
        if (this->isKeyPressed(Key::D)) actions.insert(Action::RotateRight);
        if (this->isKeyPressed(Key::W)) actions.insert(Action::ThrustForward);
        if (this->isKeyPressed(Key::S)) actions.insert(Action::ThrustBackward);
        if (this->isKeyPressed(Key::SPACE)) actions.insert(Action::ShootBullet);
        if (this->isKeyReleased(Key::SPACE)) actions.insert(Action::BulletFlagReset);
        return actions;
    }

private:

    //Fikk inspirasjon av ChatGPT om å lage et set
    std::set<Key> keys_pressed;
    std::set<Key> keys_released;


};
#endif//ASTEROIDS_SPACESHIP_KEYLISTENER_HPP