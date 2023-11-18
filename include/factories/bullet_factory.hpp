
#ifndef ASTEROIDS_BULLET_FACTORY_HPP
#define ASTEROIDS_BULLET_FACTORY_HPP

#include "object_controllers/asteroid_controller.hpp"
#include "object_factory.hpp"
#include "functions/create_sprite.hpp"
#include "functions/random_functions.hpp"
#include "threepp/threepp.hpp"
#include "object_controllers/spaceship_controller.hpp"

using namespace threepp;

class BulletFactory : public ObjectFactory {

public:

    BulletFactory(Canvas& canvas, std::shared_ptr<Scene>& scene, TextureLoader& loader, std::string material_path, float scale,
                    float velocity, float front_offset, float edge_offset)
        : ObjectFactory(canvas, scene, loader, material_path, scale, edge_offset),
          velocity_(velocity), front_offset_(front_offset) {}

    void shoot_bullet(ObjectController& spaceship) {
        auto bullet_sprite = create_object_sprite();

        bullet_sprite->material->rotation = spaceship.get_sprite()->material->rotation;

        float bullet_front_offset = bullet_sprite->scale.x * front_offset_;
        Vector2 offset_position = {
                bullet_sprite->position.x + spaceship.get_direction().x * bullet_front_offset,
                bullet_sprite->position.y + spaceship.get_direction().y * bullet_front_offset
        };
        bullet_sprite->position.set(offset_position.x, offset_position.y, 0);

        auto bullet = create_object(bullet_sprite);

        std::cout << "Bullet count after addition: " << objects.size() << std::endl;
        std::cout << "Bullet sprite count after addition: " << object_sprites.size() << std::endl;
    }

    std::shared_ptr<ObjectController> create_object(std::shared_ptr<Sprite> object_sprite) override {
        auto bullet = std::make_shared<ObjectController>(object_sprite, Vector2(0, 0),
                                                         velocity_, 0, 0, 0);
        objects.push_back(bullet);
        return bullet;
    }

private:

    float velocity_;
    float front_offset_;

};

#endif//ASTEROIDS_BULLET_FACTORY_HPP
