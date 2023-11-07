
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
    enum class action {
        rotate_left,
        rotate_right,
        thrust_forward,
        thrust_backward,
        shoot_bullet,
        bullet_reset_flag,
    };

    std::set<action> determine_action() {
        std::set<action> actions;
        if (this->isKeyPressed(Key::A)) actions.insert(action::rotate_left);
        if (this->isKeyPressed(Key::D)) actions.insert(action::rotate_right);
        if (this->isKeyPressed(Key::W)) actions.insert(action::thrust_forward);
        if (this->isKeyPressed(Key::S)) actions.insert(action::thrust_backward);
        if (this->isKeyPressed(Key::SPACE)) actions.insert(action::shoot_bullet);
        if (this->isKeyReleased(Key::SPACE)) actions.insert(action::bullet_reset_flag);
        return actions;
    }

private:

    //Fikk inspirasjon av ChatGPT om å lage et set
    std::set<Key> keys_pressed;
    std::set<Key> keys_released;


};
#endif//ASTEROIDS_SPACESHIP_KEYLISTENER_HPP