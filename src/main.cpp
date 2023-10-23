
#include "threepp/threepp.hpp"
#include "spaceship_class.hpp"

using namespace threepp;

int main() {

    Canvas canvas("Asteroids", {{"aa", 4}});
    auto size = canvas.size();
    GLRenderer renderer(canvas.size());
    renderer.setClearColor(Color::black);

    TextureLoader loader;

    SpaceshipClass spaceship(loader, "data/spaceship.png", 0.1);

    //Delen som skalerer kameraet til vinduet er skrevet med hjelp fra ChatGPT
    auto camera = OrthographicCamera::create(-size.width / 2, size.width / 2, size.height / 2, -size.height / 2, 1, 100);
    camera->position.z = 100;

    auto scene = Scene::create();
    scene->add(spaceship);

    canvas.onWindowResize([&](WindowSize size) {
        camera->left = -size.width / 2;
        camera->right = size.width / 2;
        camera->top = size.height / 2;
        camera->bottom = -size.height / 2;
        camera->updateProjectionMatrix();
        renderer.setSize(size);

        spaceship.on_window_resize();
    });

    canvas.animate([&] {
        renderer.render(*scene, *camera);
    });
}