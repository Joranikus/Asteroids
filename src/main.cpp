
#include "spaceship.hpp"
#include "sprite_generator.hpp"
#include "threepp/threepp.hpp"
using namespace threepp;

int main() {

    Canvas canvas("Asteroids", {{"aa", 4}});
    auto size = canvas.size();
    GLRenderer renderer(canvas.size());
    renderer.setClearColor(Color::black);

    TextureLoader loader;

    //Creates Spaceship
    SpriteGenerator spaceship(loader, "data/spaceship.png", 0.08);
    SpaceshipKeylistener spaceship_keylistener;
    Spaceship spaceship_physics(spaceship, size, 4, 500, 0.75,
                                loader, "data/bullet.png", 1, 1000, 0.1);

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

        spaceship.on_window_resize();
        spaceship_physics.on_window_resize(size);
    });

    auto scene = Scene::create();
    scene->add(spaceship);

    Clock clock;
    canvas.animate([&] {
        auto dt = clock.getDelta();

        auto actions = spaceship_keylistener.determine_action();
        spaceship_physics.perform_spaceship_movement(actions, dt);

        spaceship_physics.update_bullets(dt, scene);
        spaceship_physics.update(dt);

        //loops through bullets in the bullets shared pointer, and renders all the bullets in the shared vector poiner.
        for (const auto& bullet : spaceship_physics.get_bullets()) {
            scene->add(bullet->get_sprite());
        }

        renderer.render(*scene, *camera);
    });
}