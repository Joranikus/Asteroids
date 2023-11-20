
#include "factories/asteroid_factory.hpp"
#include "functions/create_sprite.hpp"
#include "controllers/spaceship_controller.hpp"
#include "threepp/threepp.hpp"
#include "collision_detectors/asteroid_bullet_collision_detector.hpp"
using namespace threepp;

int main() {

    Canvas::Parameters canvas_parameters;
    canvas_parameters.title("Asteroids").size(1280, 720).antialiasing(4);
    Canvas canvas(canvas_parameters);
    auto size = canvas.size();
    GLRenderer renderer(canvas.size());
    renderer.setClearColor(Color::black);

    std::shared_ptr<Scene> scene = Scene::create();

    TextureLoader loader;

    SpaceshipKeylistener spaceship_keylistener;

    auto spaceship_sprite = create_sprite(loader, "spaceship.png", 0.08);

    BulletFactory bullet_factory(canvas, scene, loader, "bullet.png", 1, 1000, 2.5, 0);

    SpaceshipController spaceship(canvas, bullet_factory, spaceship_sprite, 4, 500, 0.75);
    scene->add(spaceship_sprite);

    std::vector<std::string> asteroid_material_paths = {"asteroid1.png", "asteroid2.png", "asteroid3.png", "asteroid4.png",
                                                        "asteroid5.png", "asteroid6.png", "asteroid7.png", "asteroid8.png"};

    AsteroidFactory asteroid_factory(canvas, scene, loader, asteroid_material_paths,
                                     0.2, 100, 300, 0);

    AsteroidBulletCollisionDetector asteroid_bullet_collison_detector;

    //delen som skalerer kameraet til vinduet er skrevet med hjelp fra ChatGPT og godeste studass.
    //Uses the window size to create the camera
    auto camera = OrthographicCamera::create(-size.width / 2, size.width / 2, size.height / 2, -size.height / 2, 1, 100);
    camera->position.z = 100;

    canvas.addKeyListener(&spaceship_keylistener);

    canvas.onWindowResize([&](WindowSize size) {

        //Scales the camera according to the window width/height
        camera->left = -size.width / 2;
        camera->right = size.width / 2;
        camera->top = size.height / 2;
        camera->bottom = -size.height / 2;
        camera->updateProjectionMatrix();

        asteroid_factory.on_window_resize(size);
        bullet_factory.on_window_resize(size);

        renderer.setSize(size);
    });

    Clock clock;
    canvas.animate([&] {
        auto dt = clock.getDelta();
        spaceship.update(dt);
        bullet_factory.update_objects(dt);
        asteroid_factory.update_objects(dt);

        spaceship.perform_spaceship_movement(spaceship_keylistener.determine_action(), dt);

        asteroid_factory.generate_wave(dt, 20, 1, 5);

        asteroid_bullet_collison_detector.check_collision(bullet_factory.objects, asteroid_factory.objects);

        renderer.render(*scene, *camera);
    });
}