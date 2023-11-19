
#ifndef ASTEROIDS_BULLET_FACTORY_HPP
#define ASTEROIDS_BULLET_FACTORY_HPP

#include "base_factory.hpp"
#include "functions/create_sprite.hpp"
#include "functions/random_functions.hpp"
#include "object_controllers/asteroid_controller.hpp"
#include "object_controllers/bullet_controller.hpp"
#include "object_controllers/spaceship_controller.hpp"
#include "threepp/threepp.hpp"

using namespace threepp;

class BulletFactory : public BaseFactory {

public:

    BulletFactory(Canvas& canvas, std::shared_ptr<Scene>& scene, TextureLoader& loader, std::string material_path, float scale,
                    float velocity, float front_offset, float edge_offset)
        : BaseFactory(canvas, scene, loader, material_path, scale, edge_offset),
          velocity_(velocity), front_offset_(front_offset) {}

    void shoot_bullet(BaseController& spaceship) {
        auto bullet_sprite = create_object_sprite();
        bullet_sprite->material->rotation = spaceship.sprite_->material->rotation;

        float bullet_front_offset = bullet_sprite->scale.x * front_offset_;
        Vector2 direction = spaceship.get_direction();
        Vector2 position = spaceship.get_position();

        Vector2 offset_position = {
                position.x + direction.x * bullet_front_offset,
                position.y + direction.y * bullet_front_offset
        };

        bullet_sprite->position.set(offset_position.x, offset_position.y, 0);

        auto bullet = create_bullet(bullet_sprite, spaceship.get_direction());
        add_to_scene(bullet_sprite);
    }

    std::shared_ptr<BaseController> create_bullet(std::shared_ptr<Sprite>& bullet_sprite, Vector2 direction) {
        auto bullet = std::make_shared<BulletController>(bullet_sprite, direction, velocity_);
        objects.push_back(bullet);
        return bullet;
    }

private:

    float velocity_;
    float front_offset_;

};

#endif//ASTEROIDS_BULLET_FACTORY_HPP
