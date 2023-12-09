
#ifndef ASTEROIDS_BASE_FACTORY_HPP
#define ASTEROIDS_BASE_FACTORY_HPP

#include "controllers/base_controller.hpp"

class BaseFactory {

public:
    BaseFactory(threepp::Canvas& canvas,
                std::shared_ptr<threepp::Scene>& scene,
                threepp::TextureLoader& loader,
                std::string material_path,
                float scale = 1.0f,
                float edge_offset = 0.0f);

    virtual void update_objects(float dt);
    virtual void delete_object(size_t i);
    virtual bool out_of_bounds(std::shared_ptr<BaseController>& object);

    virtual std::shared_ptr<threepp::Sprite> create_object_sprite();
    virtual std::shared_ptr<BaseController> create_object(std::shared_ptr<threepp::Sprite>& object_sprite);

    virtual void add_to_scene(std::shared_ptr<threepp::Sprite>& object_sprite);
    virtual void on_window_resize(threepp::WindowSize& new_size);

    std::vector<std::shared_ptr<BaseController>> objects;
    std::vector<std::shared_ptr<threepp::Sprite>> object_sprites;

private:

    threepp::Canvas& canvas_;
    std::shared_ptr<threepp::Scene>& scene_;
    threepp::TextureLoader& loader_;
    std::string material_path_;
    float scale_;
    float edge_offset_;

    threepp::WindowSize screen_size_ = canvas_.size();
};


#endif//ASTEROIDS_BASE_FACTORY_HPP
