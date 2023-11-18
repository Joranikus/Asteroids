
#ifndef ASTEROIDS_OBJECT_FACTORY_HPP
#define ASTEROIDS_OBJECT_FACTORY_HPP

#include "object_controllers/asteroid_controller.hpp"
#include "functions/create_sprite.hpp"
#include "functions/random_functions.hpp"
#include "threepp/threepp.hpp"
using namespace threepp;

class ObjectFactory {

public:
    ObjectFactory(Canvas& canvas, std::shared_ptr<Scene>& scene, TextureLoader& loader, std::string material_path, float scale, float deletion_edge_offset)
        : canvas_(canvas), scene_(scene), loader_(loader), material_path_(material_path), scale_(scale),
          edge_offset_(deletion_edge_offset) {}

    //denne delen for å slette objekter og sprites er laget med hjelp fra ChatGPT
    virtual void update_objects(float dt) {
        std::vector<int> to_remove;

        for (size_t index = 0; index < objects.size(); ++index) {
            auto& object = objects[index];
            object->update(dt);

            if (out_of_bounds(object)) {
                to_remove.push_back(index);
            }
        }

        for (auto it = to_remove.rbegin(); it != to_remove.rend(); ++it) {
            delete_object(*it);
        }
    }

    virtual void delete_object(size_t index) {
        if (index >= objects.size() || index >= object_sprites.size()) {
            std::cerr << "Index out of bounds for deletion." << std::endl;
            return;
        }

        scene_->remove(*object_sprites[index]);

        objects.erase(objects.begin() + index);
        object_sprites.erase(object_sprites.begin() + index);
    }

    virtual bool out_of_bounds(std::shared_ptr<ObjectController>& object) {
        auto object_sprite = object->get_sprite();
        if (object_sprite->position.x < -screen_size_.width / 2 - edge_offset_ ||
            object_sprite->position.x > screen_size_.width / 2 + edge_offset_ ||
            object_sprite->position.y < -screen_size_.height / 2 - edge_offset_ ||
            object_sprite->position.y > screen_size_.height / 2 + edge_offset_) {
            return true;
        } else {
            return false;
        }
    }

    virtual std::shared_ptr<Sprite> create_object_sprite() {
        auto object_sprite = create_sprite(loader_, material_path_, scale_);
        object_sprites.push_back(object_sprite);
        return object_sprite;
    }

    virtual std::shared_ptr<ObjectController> create_object(std::shared_ptr<Sprite> object_sprite) {
        auto object = std::make_shared<ObjectController>(object_sprite, Vector2(0, 0), 0, 0, 0, 0);
        objects.push_back(object);
        return object;
    }

    virtual void add_to_scene(std::shared_ptr<Sprite> object_sprite) {
        scene_->add(object_sprite);
    }

    std::vector<std::shared_ptr<ObjectController>> objects;
    std::vector<std::shared_ptr<Sprite>> object_sprites;

private:

    Canvas& canvas_;
    WindowSize screen_size_ = canvas_.size();
    std::shared_ptr<Scene>& scene_;
    TextureLoader& loader_;
    std::string material_path_;
    float scale_;
    float edge_offset_;
};


#endif//ASTEROIDS_OBJECT_FACTORY_HPP
