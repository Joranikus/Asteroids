
#include "threepp/threepp.hpp"

using namespace threepp;

int main() {

    Canvas canvas("Asteroids", {{"aa", 4}});
    auto size = canvas.size();
    GLRenderer renderer(canvas.size());
    renderer.setClearColor(Color::black);

    //Denne delen er skrevet med inspirasjon fra ChatGPT og eksempelkode fra Threepp
    TextureLoader loader;

    auto spaceship_material = SpriteMaterial::create();
    spaceship_material->map = loader.load("data/spaceship.png");
    spaceship_material->map->offset.set(0.5, 0.5);

    auto image_width = static_cast<float>(spaceship_material->map->image->width);
    auto image_height = static_cast<float>(spaceship_material->map->image->height);

    auto scale_factor = 0.1;
    auto spaceship_sprite = Sprite::create(spaceship_material);

    spaceship_sprite->center.set(0.5, 0.5);
    spaceship_sprite->scale.set(image_width * scale_factor,  image_height * scale_factor, 1);



    auto camera = OrthographicCamera::create(-size.width / 2, size.width / 2, size.height / 2, -size.height / 2, 1, 100);
    camera->position.z = 100;

    auto scene = Scene::create();
    scene->add(spaceship_sprite);

    canvas.onWindowResize([&](WindowSize size) {
        camera->left = -size.width / 2;
        camera->right = size.width / 2;
        camera->top = size.height / 2;
        camera->bottom = -size.height / 2;
        camera->updateProjectionMatrix();
        renderer.setSize(size);

        spaceship_sprite->scale.set(image_width * scale_factor, image_height * scale_factor, 1);
    });

    canvas.animate([&] {
        renderer.render(*scene, *camera);
    });
}