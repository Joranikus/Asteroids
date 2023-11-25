
#include <catch2/catch_test_macros.hpp>
#include "controllers/base_controller.hpp"
#include "threepp/threepp.hpp"

TEST_CASE("BaseController Initialization", "[BaseController]") {
    SECTION("Constructor intializes values correctly") {
        auto sprite = Sprite::create();
        Vector2 direction = {1.0f, 0.0f};
        float rotation_speed = 2.0f;
        float friction_coefficient = 0.1f;
        float thrust_power = 3.0f;
        float initial_velocity = 4.0f;
        float initial_rotation_velocity = 5.0f;

        BaseController controller(sprite,
                                  direction,
                                  rotation_speed,
                                  friction_coefficient,
                                  thrust_power,
                                  initial_velocity,
                                  initial_rotation_velocity);
    }
}

TEST_CASE("BaseController Public Functions", "[BaseController]") {

}