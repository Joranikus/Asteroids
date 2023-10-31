
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

private:

    //Fikk inspirasjon av ChatGPT om å lage et set
    std::set<Key> keys_pressed;
};
#endif//ASTEROIDS_SPACESHIP_KEYLISTENER_HPP
