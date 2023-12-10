
#ifndef ASTEROIDS_HUD_HPP
#define ASTEROIDS_HUD_HPP

#include "threepp/threepp.hpp"
#include "controllers/base_controller.hpp"

struct HUDProperties {
    float health_text_scale = 1;
    int health_x = 0;
    int health_y = 0;

    float score_text_scale = 1;
    int score_x = 0;
    int score_y = 0;
};

class HUD {
public:
    HUD(threepp::TextRenderer& text_renderer,
               BaseController& object,
        HUDProperties& properties);

    void setup();
    void set_text();

private:

    threepp::TextRenderer& text_renderer_;
    HUDProperties& properties_;
    BaseController& object_;

    threepp::TextHandle& health_handle;
    threepp::TextHandle& score_handle;
};

#endif//ASTEROIDS_HUD_HPP
