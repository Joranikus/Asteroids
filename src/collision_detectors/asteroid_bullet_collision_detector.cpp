
#include "asteroid_bullet_collision_detector.hpp"

void AsteroidBulletCollisionDetector::check_collision(std::vector<std::shared_ptr<BaseController>>& bullet_list,
                                                      std::vector<std::shared_ptr<BaseController>>& asteroid_list) {
    for (auto& bullet : bullet_list) {
        for (auto& asteroid : asteroid_list) {
            if (collision(bullet, asteroid)) {
                bullet->marked_for_removal = true;
                asteroid->marked_for_removal = true;
                score += 10;
            }
        }
    }
}

int AsteroidBulletCollisionDetector::get_score() const {
    return score;
}