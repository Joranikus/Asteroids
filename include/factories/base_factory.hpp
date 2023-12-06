
#ifndef ASTEROIDS_BASE_FACTORY_HPP
#define ASTEROIDS_BASE_FACTORY_HPP

#include "controllers/asteroid_controller.hpp"
#include "functions/create_sprite.hpp"
#include "functions/random_functions.hpp"
#include "threepp/threepp.hpp"
#include <iostream>
using namespace threepp;

class BaseFactory {

public:
    BaseFactory(Canvas& canvas,
                std::shared_ptr<Scene>& scene,
                TextureLoader& loader,
                std::string material_path,
                float scale = 1.0f,
                float edge_offset = 0.0f)

        : canvas_(canvas),
          scene_(scene),
          loader_(loader),
          material_path_(material_path),
          scale_(scale),
          edge_offset_(edge_offset) {}

    //denne delen for å slette objekter og sprites er laget med hjelp fra ChatGPT
    virtual void update_objects(float dt) {
        std::vector<int> to_remove;

        for (size_t i = 0; i < objects.size(); ++i) {
            auto& object = objects[i];
            object->update(dt);

            if (out_of_bounds(object) || object->marked_for_removal) {
                to_remove.push_back(i);
            }
        }

        for (auto i = to_remove.rbegin(); i != to_remove.rend(); ++i) {
            delete_object(*i);
        }
    }

    virtual void delete_object(size_t i) {
        if (i >= objects.size() || i >= object_sprites.size()) {
            std::cerr << "Index out of bounds for deletion." << std::endl;
            return;
        }

        scene_->remove(*object_sprites[i]);
        objects.erase(objects.begin() + i);
        object_sprites.erase(object_sprites.begin() + i);
    }

    virtual bool out_of_bounds(std::shared_ptr<BaseController>& object) {
        auto object_sprite = object->sprite_;
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

    virtual std::shared_ptr<BaseController> create_object(std::shared_ptr<Sprite> object_sprite) {
        auto object = std::make_shared<BaseController>(object_sprite, Vector2(0, 0),
                                                       0, 0, 0, 0);
        objects.push_back(object);
        return object;
    }

    virtual void add_to_scene(std::shared_ptr<Sprite> object_sprite) {
        scene_->add(object_sprite);
    }

    virtual void on_window_resize(WindowSize& new_size) {
        screen_size_ = new_size;
    }

    std::vector<std::shared_ptr<BaseController>> objects;
    std::vector<std::shared_ptr<Sprite>> object_sprites;


private:

    Canvas& canvas_;
    std::shared_ptr<Scene>& scene_;
    TextureLoader& loader_;
    std::string material_path_;
    float scale_;
    float edge_offset_;

    WindowSize screen_size_ = canvas_.size();

};


#endif//ASTEROIDS_BASE_FACTORY_HPP
