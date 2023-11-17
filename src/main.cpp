
#include "asteroid_factory.hpp"
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

    TextureLoader loader;

    //Creates SpaceshipController
    auto spaceship_sprite = create_sprite(loader, "spaceship.png", 0.08);

    SpaceshipKeylistener spaceship_keylistener;
    SpaceshipController spaceship(spaceship_sprite, size, 4, 500, 0.75,
                        loader, "bullet.png", 1, 1000, 0.1);

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

    std::shared_ptr<Scene> scene = Scene::create();
    scene->add(spaceship_sprite);
    ////////////////////////
    AsteroidFactory asteroid_generator(size, loader, "asteroid1.png",
                                         0.2, 0, 100,300);
   /////////////////////////
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
            asteroid_generator.generate_wave(scene, dt, 10, 1);
            lol = 1;
        }

        asteroid_generator.update_asteroids(dt, scene);
        /////////////////////

        //loops through bullets in the bullets shared pointer, and renders all the bullets in the shared vector poiner.
        for (const auto& bullet : spaceship.get_bullets()) {
            scene->add(bullet->get_sprite());
        }

        renderer.render(*scene, *camera);
    });
}