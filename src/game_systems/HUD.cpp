
#include "HUD.hpp"

using namespace threepp;

HUD::HUD(TextRenderer& text_renderer,
         BaseController& object,
         HUDProperties& properties)

    : object_(object),
      text_renderer_(text_renderer),
      properties_(properties),
      health_handle(text_renderer_.createHandle()),
      score_handle(text_renderer_.createHandle()) {}

void HUD::setup() {
    health_handle.scale = properties_.health_text_scale;
    health_handle.y = properties_.health_y;
    health_handle.x = properties_.health_x;

    score_handle.scale = properties_.score_text_scale;
    score_handle.y = properties_.score_y;
    score_handle.x = properties_.score_x;
}

void HUD::set_text() {
    health_handle.setText("Health: " + std::to_string(object_.get_health()) + "%");
    score_handle.setText("Score: " + std::to_string(object_.get_score()) + "pts");
}