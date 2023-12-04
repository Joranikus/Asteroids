
#ifndef ASTEROIDS_GAME_HPP
#define ASTEROIDS_GAME_HPP

#include "factories/asteroid_factory.hpp"
#include "functions/create_sprite.hpp"
#include "controllers/spaceship_controller.hpp"
#include "threepp/threepp.hpp"
#include "collision_detectors/asteroid_bullet_collision_detector.hpp"

class Game {

public:

    Game() : canvas(threepp::Canvas::Parameters().title("Asteroids").size(1280, 720).antialiasing(4)),

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

             asteroid_material_paths({
                  "asteroid1.png", "asteroid2.png", "asteroid3.png",
                  "asteroid4.png", "asteroid5.png", "asteroid6.png",
                  "asteroid7.png", "asteroid8.png"
             }) {
    }

    void setup() {
        initialize_canvas();
        initialize_renderers();
        initialize_camera();
        initialize_spaceship();
        initialize_asteroids();
    }

    void run() {
        canvas.animate([&] {
            float dt = clock.getDelta();
            update_game(dt);
            render_game();
            on_window_resize();
        });
    }

    void pause() {}

private:
    void render_game() {
        renderer.render(*scene, *camera);
    }

    void update_game(float dt) {
        spaceship->update(dt);
        bullet_factory->update_objects(dt);
        asteroid_factory->update_objects(dt);

        spaceship->perform_spaceship_movement(spaceship_keylistener.determine_action(), dt);

        asteroid_factory->generate_wave(dt, 20, 1, 0);

        asteroid_bullet_collision_detector.check_collision(bullet_factory->objects, asteroid_factory->objects);
    }

    void initialize_canvas() {
        canvas.addKeyListener(&spaceship_keylistener);
    }

    void initialize_renderers() {
        renderer.setSize(canvas.size());
        renderer.setClearColor(threepp::Color::black);
    }

    void initialize_camera() {
        camera->position.z = 100;
    }

    void initialize_spaceship() {
        bullet_factory = std::make_unique<BulletFactory>(
                canvas,
                scene,
                loader,
                "bullet.png",
                1,
                1000,
                2.5,
                0
        );
        auto spaceship_sprite = create_sprite(loader, "spaceship.png", 0.08);
        spaceship = std::make_unique<SpaceshipController>(
                canvas,
                *bullet_factory,
                spaceship_sprite,
                4,
                500,
                0.75
        );
        scene->add(spaceship_sprite);
    }

    void initialize_asteroids() {
        asteroid_factory = std::make_unique<AsteroidFactory>(
                canvas,
                scene,
                loader,
                asteroid_material_paths,
                0.2,
                100,
                300,
                0
        );
    }

    void on_window_resize() {
        // scales the camera according to the window width/height
        canvas.onWindowResize([&](threepp::WindowSize size) {
            camera->left = -size.width / 2;
            camera->right = size.width / 2;
            camera->top = size.height / 2;
            camera->bottom = -size.height / 2;
            camera->updateProjectionMatrix();

            asteroid_factory->on_window_resize(size);
            bullet_factory->on_window_resize(size);

            renderer.setSize(size);
        });
    }

    Canvas canvas;
    GLRenderer renderer;
    std::shared_ptr<threepp::Scene> scene;
    TextureLoader loader;
    std::shared_ptr<threepp::OrthographicCamera> camera;
    Clock clock;
    SpaceshipKeylistener spaceship_keylistener;
    std::unique_ptr<BulletFactory> bullet_factory;
    std::unique_ptr<SpaceshipController> spaceship;
    std::unique_ptr<AsteroidFactory> asteroid_factory;
    AsteroidBulletCollisionDetector asteroid_bullet_collision_detector;
    std::vector<std::string> asteroid_material_paths;
};

#endif // ASTEROIDS_GAME_HPP