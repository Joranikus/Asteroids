
#ifndef ASTEROIDS_SPACESHIP_CLASS_HPP
#define ASTEROIDS_SPACESHIP_CLASS_HPP

#include "spaceship_controller.hpp"
#include "threepp/threepp.hpp"
using namespace threepp;

class SpaceshipClass : public Sprite {

public:

    SpaceshipClass(TextureLoader& loader, std::string material_path, float scale)
        : Sprite(SpriteMaterial::create()),
          loader_(loader),
          material_path_(material_path),
          scale_(scale) {

        //Jeg brukte chatGPT for å finne ut av "dynamic_pointer_cast" og skrive linjen under

        //Offsets the sprite by 0.5 and 0.5 so the sprite is centered
        auto material = std::dynamic_pointer_cast<SpriteMaterial>(this->material);
        material->map = loader_.load(material_path_);
        material->map->offset.set(0.5, 0.5);


        material_width_ = static_cast<float>(material->map->image->width);
        material_height_ = static_cast<float>(material->map->image->height);

        this->scale.set(material_width_ * scale_, material_height_ * scale_, 0);
    }

    //updates scale when window is resized
    void on_window_resize() {
        this->scale.set(material_width_ * scale_, material_height_ * scale_, 0);

    }

private:

    TextureLoader& loader_;
    std::string material_path_;
    float scale_;
    float material_height_;
    float material_width_;

};

#endif//ASTEROIDS_SPACESHIP_CLASS_HPP
