
#include "controllers/bullet_controller.hpp"
#include "threepp/threepp.hpp"
#include "bullet_factory.hpp"

using namespace threepp;

BulletFactory::BulletFactory(Canvas& canvas,
                             std::shared_ptr<Scene>& scene,
                             TextureLoader& loader,
                             std::string material_path,
                             const float scale,
                             const float velocity,
                             const float front_offset,
                             const float edge_offset)

    : BaseFactory(canvas,
                  scene,
                  loader,
                  std::move(material_path),
                  scale,
                  edge_offset),

      velocity_(velocity),
      front_offset_(front_offset) {}

void BulletFactory::shoot_bullet(BaseController& spaceship) {
    auto bullet_sprite = create_object_sprite();
    bullet_sprite->material->rotation = spaceship.sprite_->material->rotation;

    float bullet_front_offset = bullet_sprite->scale.x * front_offset_;
    Vector2 direction = spaceship.get_direction();
    Vector2 position = spaceship.get_position();

    Vector2 offset_position = {
            position.x + direction.x * bullet_front_offset,
            position.y + direction.y * bullet_front_offset};

    bullet_sprite->position.set(offset_position.x, offset_position.y, 0);

    auto bullet = create_bullet(bullet_sprite, spaceship.get_direction());
    add_to_scene(bullet_sprite);
}

std::shared_ptr<BaseController> BulletFactory::create_bullet(std::shared_ptr<Sprite>& bullet_sprite, Vector2 direction) {
    auto bullet = std::make_shared<BulletController>(bullet_sprite, direction, velocity_);
    objects.emplace_back(bullet);
    return bullet;
}