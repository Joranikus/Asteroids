#include "threepp/threepp.hpp"

using namespace threepp;

//lånt kode fra feedback
std::shared_ptr<Sprite> create_sprite(TextureLoader& loader,
                                      const std::string& material_path,
                                      float scale) {

    auto sprite = Sprite::create();
    auto material = sprite->material;
    material->map = loader.load(material_path);

    auto material_width = static_cast<float>(material->map->image->width);
    auto material_height = static_cast<float>(material->map->image->height);

    sprite->scale.set(material_width * scale, material_height * scale, 0);

    material->map->offset.set(0.5, 0.5);

    return sprite;
}