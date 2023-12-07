
#ifndef ASTEROIDS_SPACESHIP_KEYLISTENER_HPP
#define ASTEROIDS_SPACESHIP_KEYLISTENER_HPP

#include "threepp/threepp.hpp"
#include <set>

//inserts and erases keys from a set so multiple keys can be pressed at the same time
class SpaceshipKeylistener : public threepp::KeyListener {

public:
    void onKeyPressed(threepp::KeyEvent evt) override;
    void onKeyReleased(threepp::KeyEvent evt) override;
    bool isKeyPressed(threepp::Key key) const;
    bool isKeyReleased(threepp::Key key) const;

    //fikk inspirasjon fra chat gpt til å lage en enum class
    enum class Action {
        RotateLeft,
        RotateRight,
        ThrustForward,
        ThrustBackward,
        ShootBullet,
        BulletFlagReset,
    };

    std::set<Action> determine_action();

private:
    //Fikk inspirasjon av ChatGPT om å lage et set
    std::set<threepp::Key> keys_pressed;
    std::set<threepp::Key> keys_released;

};

#endif//ASTEROIDS_SPACESHIP_KEYLISTENER_HPP