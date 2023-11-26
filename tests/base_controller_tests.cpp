
#include "controllers/base_controller.hpp"
#include "threepp/threepp.hpp"
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

auto sprite_with_material = Sprite::create(SpriteMaterial::create());
auto sprite_without_material = Sprite::create(nullptr);
float float_tolerance = 0.001f;

TEST_CASE("BaseController Initialization", "[BaseController]") {
    BaseController controller(sprite_with_material,
                              {1.0f, 0.0f},
                              2.0f,
                              0.1f,
                              3.0f,
                              4.0f,
                              5.0f);

    SECTION("Constructor intializes values correctly") {


        REQUIRE_FALSE(controller.marked_for_removal);
        REQUIRE_THAT(controller.get_direction().x, Catch::Matchers::WithinRel(1.0f, float_tolerance));
        REQUIRE_THAT(controller.get_direction().y, Catch::Matchers::WithinRel(0.0f, float_tolerance));
        REQUIRE_THAT(controller.get_rotation_speed(), Catch::Matchers::WithinRel(2.0f, float_tolerance));
    }

    SECTION("Exception for null sprite") {
        REQUIRE_THROWS_AS(BaseController(nullptr, {1.0f, 0.0f}, 2.0f, 0.1f, 3.0f, 4.0f, 5.0f),
                          std::exception);
    }

    SECTION("Exception for missing sprite material") {
        REQUIRE_THROWS_AS(BaseController(sprite_without_material, {1.0f, 0.0f}, 2.0f, 0.1f, 3.0f, 4.0f, 5.0f),
                          std::exception);
    }

    SECTION("Exception for non-normalized directon") {
        REQUIRE_THROWS_AS(BaseController(sprite_with_material, {0.6f, 1.0f}, 2.0f, 0.1f, 3.0f, 4.0f, 5.0f),
                          std::exception);
    }

    SECTION("Exception for below zero friction") {
        REQUIRE_THROWS_AS(BaseController(sprite_with_material, {1.0f, 0.0f}, 2.0f, -0.1f, 3.0f, 4.0f, 5.0f),
                          std::exception);
    }

    SECTION("Exception for above 1 friction") {
        REQUIRE_THROWS_AS(BaseController(sprite_with_material, {1.0f, 0.0f}, 2.0f, 1.1f, 3.0f, 4.0f, 5.0f),
                          std::exception);
    }

    SECTION("Exception for negative thrust power") {
        REQUIRE_THROWS_AS(BaseController(sprite_with_material, {1.0f, 0.0f}, 2.0f, 0.1f, -3.0f, 4.0f, 5.0f),
                          std::exception);
    }
}

TEST_CASE("BaseController Public Functions", "[BaseController]") {
    BaseController controller(sprite_with_material,
                              {1.0f, 0.0f},
                              2.0f,
                              0.1f,
                              3.0f,
                              4.0f,
                              5.0f);

    SECTION("update()") {

    }

    SECTION("rotate_counter_clockwise") {

    }

    SECTION("rotate_clockwise") {

    }

    SECTION("thrust_forward") {

    }

    SECTION("thrust_backward") {

    }

    SECTION("set_direction() with normalized direction") {
        Vector2 new_direction = {1.0f, 0.0f};
        controller.set_direction(new_direction);
        REQUIRE(controller.get_direction() == new_direction);
    }

    SECTION("Exception for non-normalized direction in set_direction()") {
        REQUIRE_THROWS_AS(controller.set_direction({0.6f, 1.0f}), std::exception);
    }
}