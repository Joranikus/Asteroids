
#include "controllers/spaceship_controller.hpp"
#include "factories/asteroid_factory.hpp"
#include "functions/create_sprite.hpp"
#include "threepp/threepp.hpp"
#include "game_systems/game.hpp"

using namespace threepp;

Game::Game(): canvas(threepp::Canvas::Parameters().title("Asteroids").size(1280, 720).antialiasing(4)),

              scene(threepp::Scene::create()),

              renderer(canvas.size()),

              // delen som skalerer kameraet til vinduet er skrevet med hjelp fra ChatGPT og godeste studass.
              // Uses the window size to create the camera
              camera(threepp::OrthographicCamera::create(
                      -canvas.size().width / 2,
                      canvas.size().width / 2,
                      canvas.size().height / 2,
                      -canvas.size().height / 2,
                      1, 100)),

              asteroid_material_paths({"asteroid1.png", "asteroid2.png", "asteroid3.png",
                                       "asteroid4.png", "asteroid5.png", "asteroid6.png",
                                       "asteroid7.png", "asteroid8.png"}) {}

void Game::setup() {
    initialize_canvas();
    initialize_renderers();
    initialize_camera();
    initialize_game_points();
    initialize_spaceship();
    initialize_asteroids();

    spaceship_points->setup();
}

void Game::run() {
    canvas.onWindowResize([&](WindowSize size) {
        on_window_resize(size);
    });

    canvas.animate([&] {
        float dt = clock.getDelta();
        update_game(dt);
        render_game();
    });
}

void Game::render_game() {
    spaceship_points->set_text();
    renderer.render(*scene, *camera);

    renderer.resetState();
    text_renderer.render();
}

void Game::update_game(float dt) {
    spaceship->update(dt);
    bullet_factory->update_objects(dt);
    asteroid_factory->update_objects(dt);

    spaceship->perform_spaceship_movement(spaceship_keylistener.determine_action(), dt);

    asteroid_factory->generate_wave(dt, 20, 1, 0);

    asteroid_bullet_collision_detector.check_collision(bullet_factory->objects, asteroid_factory->objects);
    spaceship->set_score(asteroid_bullet_collision_detector.get_score());

    asteroid_collision_detector.check_collision(asteroid_factory->objects);
}

void Game::initialize_canvas() {
    canvas.addKeyListener(&spaceship_keylistener);
}

void Game::initialize_renderers() {
    renderer.setSize(canvas.size());
    renderer.setClearColor(threepp::Color::black);
}

void Game::initialize_camera() {
    camera->position.z = 100;
}

void Game::initialize_spaceship() {
    bullet_factory = std::make_unique<BulletFactory>(
            canvas,
            scene,
            loader,
            "bullet.png",
            1,
            1000,
            2.5,
            0);

    auto spaceship_sprite = create_sprite(loader, "spaceship.png", 0.08);
    spaceship = std::make_unique<SpaceshipController>(
            canvas,
            *bullet_factory,
            spaceship_sprite,
            4,
            500,
            0.75);
    scene->add(spaceship_sprite);

    spaceship_points = std::make_unique<HUD>(
            text_renderer,
            *spaceship,
            *spaceship_point_props);
}

void Game::initialize_asteroids() {
    asteroid_factory = std::make_unique<AsteroidFactory>(
            canvas,
            scene,
            loader,
            asteroid_material_paths,
            0.2,
            100,
            300,
            0);
}

void Game::initialize_game_points() {
    spaceship_point_props = std::make_unique<HUDProperties>();
    spaceship_point_props->health_text_scale = 2;
    spaceship_point_props->health_x = 10;
    spaceship_point_props->health_y = 10;
    spaceship_point_props->score_text_scale = 2;
    spaceship_point_props->score_x = 10;
    spaceship_point_props->score_y = 40;
}

void Game::on_window_resize(WindowSize size) {
    // scales the camera according to the window width/height
    camera->left = -size.width / 2;
    camera->right = size.width / 2;
    camera->top = size.height / 2;
    camera->bottom = -size.height / 2;
    camera->updateProjectionMatrix();

    spaceship->on_window_resize(size);
    asteroid_factory->on_window_resize(size);
    bullet_factory->on_window_resize(size);

    renderer.setSize(size);
}