
#include "base_factory.hpp"
#include "functions/create_sprite.hpp"
#include <iostream>

using namespace threepp;

BaseFactory::BaseFactory(Canvas& canvas,
                         std::shared_ptr<Scene>& scene,
                         TextureLoader& loader,
                         std::string material_path,
                         float scale,
                         float edge_offset)

    : canvas_(canvas),
      scene_(scene),
      loader_(loader),
      material_path_(std::move(material_path)),
      scale_(scale),
      edge_offset_(edge_offset) {}

// denne delen for å slette objekter og sprites er laget med hjelp fra ChatGPT
void BaseFactory::update_objects(float dt) {
    std::vector<int> to_remove;

    for (int i = 0; i < objects.size(); ++i) {
        auto& object = objects[i];
        object->update(dt);

        if (out_of_bounds(object) || object->marked_for_removal) {
            to_remove.emplace_back(i);
        }
    }

    for (auto i = to_remove.rbegin(); i != to_remove.rend(); ++i) {
        delete_object(*i);
    }
}

void BaseFactory::delete_object(size_t i) {
    if (i >= objects.size() || i >= object_sprites.size()) {
        std::cerr << "Index out of bounds for deletion." << std::endl;
        return;
    }

    scene_->remove(*object_sprites[i]);
    objects.erase(objects.begin() + i);
    object_sprites.erase(object_sprites.begin() + i);
}

bool BaseFactory::out_of_bounds(std::shared_ptr<BaseController>& object) {
    auto object_sprite = object->sprite_;
    if (object_sprite->position.x < static_cast<float>(-screen_size_.width) / 2 - edge_offset_ ||
        object_sprite->position.x > static_cast<float>(screen_size_.width) / 2 + edge_offset_ ||
        object_sprite->position.y < static_cast<float>(-screen_size_.height) / 2 - edge_offset_ ||
        object_sprite->position.y > static_cast<float>(screen_size_.height) / 2 + edge_offset_) {
        return true;
    } else {
        return false;
    }
}

std::shared_ptr<Sprite> BaseFactory::create_object_sprite() {
    auto object_sprite = create_sprite(loader_, material_path_, scale_);
    object_sprites.emplace_back(object_sprite);
    return object_sprite;
}

std::shared_ptr<BaseController> BaseFactory::create_object(std::shared_ptr<Sprite> object_sprite) {
    auto object = std::make_shared<BaseController>(object_sprite,
                                                                Vector2(0, 0),
                                                                0,
                                                                0,
                                                                0,
                                                                0);

    objects.emplace_back(object);
    return object;
}

void BaseFactory::add_to_scene(std::shared_ptr<Sprite> object_sprite) {
    scene_->add(object_sprite);
}

void BaseFactory::on_window_resize(WindowSize& new_size) {
    screen_size_ = new_size;
}