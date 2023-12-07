
#include "spaceship_keylistener.hpp"

using namespace threepp;

    void SpaceshipKeylistener::onKeyPressed(KeyEvent evt) {
        keys_pressed.insert(evt.key);
        keys_released.erase(evt.key);
    }

    void SpaceshipKeylistener::onKeyReleased(KeyEvent evt) {
        keys_pressed.erase(evt.key);
        keys_released.insert(evt.key);
    }

    bool SpaceshipKeylistener::isKeyPressed(Key key) const {
        return keys_pressed.find(key) != keys_pressed.end();
    }

    bool SpaceshipKeylistener::isKeyReleased(Key key) const {
        return keys_released.find(key) != keys_released.end();
    }

    std::set<SpaceshipKeylistener::Action> SpaceshipKeylistener::determine_action() {
        std::set<Action> actions;
        if (this->isKeyPressed(Key::A)) actions.insert(Action::RotateLeft);
        if (this->isKeyPressed(Key::D)) actions.insert(Action::RotateRight);
        if (this->isKeyPressed(Key::W)) actions.insert(Action::ThrustForward);
        if (this->isKeyPressed(Key::S)) actions.insert(Action::ThrustBackward);
        if (this->isKeyPressed(Key::SPACE)) actions.insert(Action::ShootBullet);
        if (this->isKeyReleased(Key::SPACE)) actions.insert(Action::BulletFlagReset);
        return actions;
    }