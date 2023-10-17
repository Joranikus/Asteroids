
#include "threepp/threepp.hpp"

using namespace threepp;

int main() {

    Canvas canvas("Asteroids", {{"aa", 4}});
    GLRenderer renderer(canvas.size());
    renderer.setClearColor(Color::black);

    auto camera = OrthographicCamera::create();
    camera->position.z = 5;

    auto scene = Scene::create();

    canvas.onWindowResize([&](WindowSize size) {

        camera->updateProjectionMatrix();
        renderer.setSize(size);

    });

    canvas.animate([&] {

        renderer.render(*scene, *camera);

    });
}