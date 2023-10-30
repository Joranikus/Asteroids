

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

       //Jeg brukte chatGPT for å finne ut av "dynamic_pointer_cast" og skrive linjen under
       auto material = std::dynamic_pointer_cast<SpriteMaterial>(this->material);
       material->map = loader_.load(material_path_);

       material_width_ = static_cast<float>(material->map->image->width);
       material_height_ = static_cast<float>(material->map->image->height);

       this->scale.set(material_width_ * scale_, material_height_ * scale_, 0);

   }

   //sets image offset
   void set_offset(float x_offset, float y_offset) {
       material->map->offset.set(x_offset, y_offset);
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

#endif//ASTEROIDS_SPRITE_GENERATOR_HPP
