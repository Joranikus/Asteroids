
#include "controllers/base_controller.hpp"
#include "threepp/threepp.hpp"
#include <catch2/catch_all.hpp>

//fixture created with help from ChatGPT
class BaseControllerFixture {
public:
    BaseControllerFixture() {
        sprite_with_material = Sprite::create(SpriteMaterial::create());
        sprite_without_material = Sprite::create(nullptr);
        //creating a controller with normal working values
        controller = std::make_unique<BaseController>(sprite_with_material, //sprite
                                                           Vector2{0.5f, 0.5f}, //object in north-east direction
                                                           2.0f, //2 rotation speed
                                                           0.1f, //0.1 / 10% friction
                                                           3.0f, //3 thrust power
                                                           4.0f, //4 initial velocity
                                                           5.0f); //5 initial rotation velocity
    }

    std::shared_ptr<Sprite> sprite_with_material;
    std::shared_ptr<Sprite> sprite_without_material;
    std::unique_ptr<BaseController> controller;
};

float float_tolerance = 0.00001f;

TEST_CASE_METHOD(BaseControllerFixture, "BaseController Constructor", "[BaseController]") {

    SECTION("Constructor initializes values correctly") { // tests that the object is NOT marked for removal, and that the getter values are correct
        REQUIRE_FALSE(controller->marked_for_removal);
        REQUIRE_THAT(controller->get_direction().x, Catch::Matchers::WithinRel(0.5f, float_tolerance));
        REQUIRE_THAT(controller->get_direction().y, Catch::Matchers::WithinRel(0.5f, float_tolerance));
        REQUIRE_THAT(controller->get_rotation_speed(), Catch::Matchers::WithinRel(2.0f, float_tolerance));
    }

    SECTION("Exception for null sprite") { // sets the sprite as a nullptr, to test if the constructor throws an exception
        REQUIRE_THROWS_AS(BaseController(nullptr, {1.0f, 0.0f}, 2.0f, 0.1f, 3.0f, 4.0f, 5.0f),
                          std::exception);
    }

    SECTION("Exception for missing sprite material") { // sets the sprite material as a nullptr, to test if the constructor throws an exception
        REQUIRE_THROWS_AS(BaseController(sprite_without_material, {1.0f, 0.0f}, 2.0f, 0.1f, 3.0f, 4.0f, 5.0f),
                          std::exception);
    }

    SECTION("Exception for non-normalized directon") { // sets a non-normalized direction vector to test if the function throws an exception
        REQUIRE_THROWS_AS(BaseController(sprite_with_material, {0.6f, 1.0f}, 2.0f, 0.1f, 3.0f, 4.0f, 5.0f),
                          std::exception);
    }

    SECTION("Exception for below zero friction") { // sets a negative friction to test if the function throws an exception
        REQUIRE_THROWS_AS(BaseController(sprite_with_material, {1.0f, 0.0f}, 2.0f, -0.1f, 3.0f, 4.0f, 5.0f),
                          std::exception);
    }

    SECTION("Exception for above 1 friction") { // sets an above 100% friction to test if the function throws an exception
        REQUIRE_THROWS_AS(BaseController(sprite_with_material, {1.0f, 0.0f}, 2.0f, 1.1f, 3.0f, 4.0f, 5.0f),
                          std::exception);
    }

    SECTION("Exception for negative thrust power") { // sets a negative thrust to test if the function throws an exception
        REQUIRE_THROWS_AS(BaseController(sprite_with_material, {1.0f, 0.0f}, 2.0f, 0.1f, -3.0f, 4.0f, 5.0f),
                          std::exception);
    }
}

TEST_CASE_METHOD(BaseControllerFixture, "BaseController Public Functions", "[BaseController]") {

    // these sections with the physics was written with the help of ChatGPT
    SECTION("Zero time step") { // if DT is zero no time has passed and the object should stay in the same position as previously
        Vector2 initial_position = controller->get_position();
        float initial_rotation = controller->sprite_->material->rotation;

        controller->update(0.0f);

        auto new_position = controller->get_position();
        auto new_rotation = controller->sprite_->material->rotation;

        //since no position should have changed we can compare to the initial position
        REQUIRE_THAT(new_position.x, Catch::Matchers::WithinRel(initial_position.x, float_tolerance));
        REQUIRE_THAT(new_position.y, Catch::Matchers::WithinRel(initial_position.y, float_tolerance));

        //since no rotation should have changed we can compare to the initial rotation
        REQUIRE_THAT(new_rotation, Catch::Matchers::WithinRel(initial_rotation, float_tolerance));
    }

    //TODO: FORSETT NEDENFOR

    SECTION("Normal time step") { // if DT is 1, the object should have moved for 1 seconds
        Vector2 initial_position = controller->get_position();
        float initial_rotation = controller->sprite_->material->rotation;

        controller->update(1.0f);

        auto new_position = controller->get_position();
        auto new_velocity = controller->get_velocity();
        auto new_rotation = controller->sprite_->material->rotation;

        // should no longer be in the same position
        REQUIRE(new_position.x != initial_position.x);


        REQUIRE(new_velocity.x != initial_position.y);

        // should no longer be in the same rotation
        REQUIRE(new_rotation != initial_rotation);
    }

    SECTION("rotate_counter_clockwise") { // if DT is 1, the object should have rotated cw for 1 seconds
        float initial_rotation = controller.sprite_->material->rotation;

        controller.rotate_counter_clockwise(1.0f);

        auto new_rotation = controller.sprite_->material->rotation;

        // checks that rotation has increased
        REQUIRE(new_rotation > initial_rotation);
    }

    SECTION("rotate_clockwise") { // if DT is 1, the object should have rotated ccw for 1 seconds
        float initial_rotation = controller.sprite_->material->rotation;

        controller.rotate_clockwise(1.0f);

        auto new_rotation = controller.sprite_->material->rotation;

        // checks that rotation has decreased
        REQUIRE(new_rotation < initial_rotation);
    }

    SECTION("thrust_forward") { // if DT is 1, the object should have thrusted forward for 1 seconds
        Vector2 initial_velocity = controller.get_velocity();

        controller.thrust_forward(1.0f);

        auto new_velocity = controller.get_velocity();

        // checks that velocity has increased in the direction of the sprite
        REQUIRE(new_velocity.length() > initial_velocity.length());
    }

    SECTION("thrust_backward") {
        Vector2 initial_velocity = controller.get_velocity();

        controller.thrust_backward(1.0f);

        auto new_velocity = controller.get_velocity();

        // checks that velocity has changed appropriately
        REQUIRE(new_velocity.length() != initial_velocity.length());
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