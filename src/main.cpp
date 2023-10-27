
#include "threepp/threepp.hpp"
#include "spaceship_class.hpp"
#include "spaceship_physics.hpp"
using namespace threepp;

int main() {

    Canvas canvas("Asteroids", {{"aa", 4}});
    auto size = canvas.size();
    GLRenderer renderer(canvas.size());
    renderer.setClearColor(Color::black);

    TextureLoader loader;

    //Creates Spaceship
    SpaceshipClass spaceship(loader, "data/spaceship.png", 0.08);
    SpaceshipKeylistener spaceship_keylistener;
    SpaceshipController spaceship_controller;
    SpaceshipPhysics spaceship_physics(spaceship, 3, 200);


    //Delen som skalerer kameraet til vinduet er skrevet med hjelp fra ChatGPT og godeste studass.
    //Uses the window size to create the camera
    auto camera = OrthographicCamera::create(-size.width / 2, size.width / 2, size.height / 2, -size.height / 2, 1, 100);
    camera->position.z = 100;

    auto scene = Scene::create();
    scene->add(spaceship);

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
    });

    Clock clock;
    canvas.animate([&] {
        auto dt = clock.getDelta();

        auto actions = spaceship_controller.determine_action(spaceship_keylistener);
        spaceship_physics.perform_spaceship_movement(actions, dt);
        spaceship_physics.update(dt);

        renderer.render(*scene, *camera);
    });
}