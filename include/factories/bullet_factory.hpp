
#ifndef ASTEROIDS_BULLET_FACTORY_HPP
#define ASTEROIDS_BULLET_FACTORY_HPP

#include "threepp/threepp.hpp"
#include "base_factory.hpp"

class BulletFactory : public BaseFactory {

public:
    BulletFactory(threepp::Canvas& canvas,
                  std::shared_ptr<threepp::Scene>& scene,
                  threepp::TextureLoader& loader,
                  std::string material_path,
                  float scale,
                  float velocity,
                  float front_offset,
                  float edge_offset);

    void shoot_bullet(BaseController& spaceship);
    std::shared_ptr<BaseController> create_bullet(std::shared_ptr<threepp::Sprite>& bullet_sprite,
                                                  threepp::Vector2 direction);

private:
    float velocity_;
    float front_offset_;
};

#endif//ASTEROIDS_BULLET_FACTORY_HPP