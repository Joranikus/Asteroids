
#include <catch2/catch_all.hpp>
#include "controllers/base_controller.hpp"
#include "threepp/threepp.hpp"

//fixture created with help from ChatGPT
class BaseControllerFixture {
public:
    BaseControllerFixture() {
        sprite_with_material = Sprite::create(SpriteMaterial::create());
        sprite_without_material = Sprite::create(nullptr);

        float north_east_radian = math::TWO_PI / 4;
        Vector2 north_east_direction = {sinf(north_east_radian), cosf(north_east_radian)};

        //creating a controller with normal working values
        controller = std::make_unique<BaseController>(sprite_with_material, //sprite
                                                           north_east_direction, //object in north-east direction
                                                           2.0f, //2 rotation speed
                                                           0.1f, //0.1 / 10% friction
                                                           30.0f, //3 thrust power
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
        //object should not be marked for removal when created
        REQUIRE_FALSE(controller->marked_for_removal);

        auto direction = controller->get_direction();

        //checks if the direction is correct
        REQUIRE_THAT(std::sqrt(direction.x * direction.x + direction.y * direction.y), Catch::Matchers::WithinRel(1.0f, float_tolerance));

        //rotation speed should be retained
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

    SECTION("Exception for negative rotation speed") { // sets a negative rotation speed to test if the constructor throws an exception
        REQUIRE_THROWS_AS(BaseController(sprite_with_material, {1.0f, 0.0f}, -2.0f, 0.1f, 3.0f, 4.0f, 5.0f),
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

TEST_CASE_METHOD(BaseControllerFixture, "BaseController Update Function", "[BaseController]") {

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

    SECTION("Normal time step") { //this tests if the objects have changed according to the function
        Vector2 initial_position = controller->get_position();
        Vector2 initial_velocity = controller->get_velocity();
        float initial_rotation = controller->sprite_->material->rotation;

        controller->update(1.0f);

        auto new_position = controller->get_position();
        auto new_velocity = controller->get_velocity();
        auto new_rotation = controller->sprite_->material->rotation;

        // checks if the new position is different from the initial position
        REQUIRE_FALSE(Catch::Matchers::WithinRel(initial_position.x, float_tolerance).match(new_position.x));
        REQUIRE_FALSE(Catch::Matchers::WithinRel(initial_position.y, float_tolerance).match(new_position.y));

        // since the object has traveled for a period without thrust, and it has 10% friction, the object
        // should have changed velocity
        REQUIRE_FALSE(Catch::Matchers::WithinRel(initial_velocity.x, float_tolerance).match(new_velocity.x));
        REQUIRE_FALSE(Catch::Matchers::WithinRel(initial_velocity.y, float_tolerance).match(new_velocity.y));

        // since the object has rotated for a period, the object should be in another rotation
        REQUIRE_FALSE(Catch::Matchers::WithinRel(initial_rotation, float_tolerance).match(new_rotation));
    }
}
TEST_CASE_METHOD(BaseControllerFixture, "BaseController Rotation Functions", "[BaseController]") {
    SECTION("rotate_counter_clockwise") { // if DT is 1, the object should have rotated ccw for 1 seconds
        float initial_rotation = controller->sprite_->material->rotation;

        controller->rotate_counter_clockwise(1.0f);

        auto new_rotation = controller->sprite_->material->rotation;

        // since the object has rotated for a period, the object should be in another rotation
        REQUIRE_FALSE(Catch::Matchers::WithinRel(initial_rotation, float_tolerance).match(new_rotation));
    }

    SECTION("rotate_clockwise") { // if DT is 1, the object should have rotated cw for 1 seconds
        float initial_rotation = controller->sprite_->material->rotation;

        controller->rotate_clockwise(1.0f);

        auto new_rotation = controller->sprite_->material->rotation;

        // since the object has rotated for a period, the object should be in another rotation
        REQUIRE_FALSE(Catch::Matchers::WithinRel(initial_rotation, float_tolerance).match(new_rotation));
    }
}
//fikk hjelp av chatGPT til å skrive disse thrust testene
TEST_CASE_METHOD(BaseControllerFixture, "BaseController Thrust Functions", "[BaseController]") {
    SECTION("thrust_forward") {
        // Set initial direction (facing upwards)
        controller->set_direction({0.0f, 1.0f});

        // Set initial velocity to indicate upward movement
        Vector2 initial_velocity = {0.0f, 10.0f}; // moving upwards
        controller->set_velocity(initial_velocity);

        // apply thrust upward
        controller->thrust_forward(1.0f); // apply for 1 second

        Vector2 new_velocity = controller->get_velocity();

        // checks if the y-component of velocity has become more negative (increased downward speed)
        REQUIRE(new_velocity.y > initial_velocity.y);
    }


    SECTION("thrust_backward") {
        // set initial direction (facing upwards)
        controller->set_direction({0.0f, 1.0f});

        // set initial velocity to indicate downward movement
        Vector2 initial_velocity = {0.0f, -10.0f}; // moving downwards
        controller->set_velocity(initial_velocity);

        // apply thrust backward
        controller->thrust_backward(1.0f); // apply for 1 second

        Vector2 new_velocity = controller->get_velocity();

        // checks if the y-component of velocity has become more negative (increased downward speed)
        REQUIRE(new_velocity.y < initial_velocity.y);
    }
}

TEST_CASE_METHOD(BaseControllerFixture, "BaseController Setter Functions", "[BaseController]") {
    SECTION("set_direction() with normalized direction") {
        Vector2 new_direction = {1.0f, 0.0f};
        controller->set_direction(new_direction);
        REQUIRE(controller->get_direction() == new_direction);
    }

    SECTION("Exception for non-normalized direction in set_direction()") {
        REQUIRE_THROWS_AS(controller->set_direction({0.6f, 1.0f}), std::exception);
    }
}