

#ifndef ASTEROIDS_SPRITE_GENERATOR_HPP
#define ASTEROIDS_SPRITE_GENERATOR_HPP

#include "threepp/threepp.hpp"

using namespace threepp;

class SpriteGenerator : public Sprite {

public:
   SpriteGenerator(TextureLoader& loader, const std::string material_path, float scale)
    : Sprite(SpriteMaterial::create()),
      loader_(loader),
      material_path_(material_path),
      scale_(scale) {

       auto material = this->material;
       auto nana = this->material;
       material->map = loader_.load(material_path_);

       material_width_ = static_cast<float>(material->map->image->width);
       material_height_ = static_cast<float>(material->map->image->height);

       this->scale.set(material_width_ * scale_, material_height_ * scale_, 0);

       material->map->offset.set(0.5, 0.5);
   }

   //updates scale when window is resized
   void on_window_resize() {
       this->scale.set(material_width_ * scale_, material_height_ * scale_, 0);
   }

   Sprite* get_generated_sprite() {
       return this;
   }

   private:
       TextureLoader& loader_;
       std::string material_path_;
       float scale_;
       float material_height_;
       float material_width_;
};

#endif//ASTEROIDS_SPRITE_GENERATOR_HPP
