
#ifndef ASTEROIDS_CREATE_SPRITE_HPP
#define ASTEROIDS_CREATE_SPRITE_HPP

#include "threepp/threepp.hpp"

std::shared_ptr<threepp::Sprite> create_sprite(threepp::TextureLoader& loader,
                                               const std::string& material_path,
                                               float scale);

#endif//ASTEROIDS_CREATE_SPRITE_HPP
