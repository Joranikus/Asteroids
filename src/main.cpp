
#include "factories/asteroid_factory.hpp"
#include "functions/create_sprite.hpp"
#include "object_controllers/spaceship_controller.hpp"
#include "threepp/threepp.hpp"
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

    BulletFactory bullet_factory(canvas, scene, loader, "bullet.png", 0.1, 1000, 0.3, 0);

    SpaceshipController spaceship(canvas, bullet_factory, spaceship_sprite, 4, 500, 0.75);

    AsteroidFactory asteroid_factory(canvas, scene, loader, "asteroid1.png",
                                     0.2, 100, 300, 0);

    //Delen som skalerer kameraet til vinduet er skrevet med hjelp fra ChatGPT og godeste studass.
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

        renderer.setSize(size);

        spaceship.on_window_resize(size);
    });

    scene->add(spaceship_sprite);

    Clock clock;
    canvas.animate([&] {
        auto dt = clock.getDelta();

        auto actions = spaceship_keylistener.determine_action();
        spaceship.perform_spaceship_movement(actions, dt);

        spaceship.update_bullets(dt, scene);
        spaceship.update(dt);
        /////////////////////

        int lol;
        if (lol != 1) {
            asteroid_factory.generate_wave(dt, 10, 1);
            lol = 1;
        }

        asteroid_factory.update_objects(dt);
        /////////////////////

        //loops through bullets in the bullets shared pointer, and renders all the bullets in the shared vector poiner.
        for (const auto& bullet : spaceship.get_bullets()) {
            scene->add(bullet->get_sprite());
        }

        for (size_t bullet_index = 0; bullet_index < spaceship.get_bullets().size(); ++bullet_index) {
            auto& bullet = spaceship.get_bullets()[bullet_index];
            bool bullet_deleted = false;

            for (size_t asteroid_index = 0; asteroid_index < asteroid_factory.objects.size(); ++asteroid_index) {
                auto& asteroid = asteroid_factory.objects[asteroid_index];

                if (bullet->check_collision(asteroid)) {
                    asteroid_factory.delete_object(asteroid_index);
                    spaceship.delete_bullet(scene, bullet_index);

                    bullet_deleted = true;
                    break; // break out of the inner loop if the bullet is deleted
                }
            }

            if (bullet_deleted) {
                break; // break out of the outer loop if the bullet is deleted
            }
        }

        renderer.render(*scene, *camera);
    });
}