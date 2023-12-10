
#ifndef ASTEROIDS_GAME_HPP
#define ASTEROIDS_GAME_HPP

#include "HUD.hpp"
#include "collision_detectors/asteroid_bullet_collision_detector.hpp"
#include "collision_detectors/elastic_collision_detector.hpp"
#include "controllers/spaceship_controller.hpp"
#include "factories/asteroid_factory.hpp"
#include "threepp/threepp.hpp"

class Game {

public:
    Game();

    void setup();
    void run();

private:
    void render_game();
    void update_game(float dt);

    void initialize_canvas();
    void initialize_renderers();
    void initialize_camera();
    void initialize_spaceship();
    void initialize_asteroids();
    void initialize_game_points();

    void on_window_resize(threepp::WindowSize size);

    threepp::Canvas canvas;
    threepp::GLRenderer renderer;
    threepp::TextRenderer text_renderer;
    std::shared_ptr<threepp::Scene> scene;
    threepp::TextureLoader loader;
    std::shared_ptr<threepp::OrthographicCamera> camera;
    threepp::Clock clock;

    SpaceshipKeylistener spaceship_keylistener;
    std::unique_ptr<BulletFactory> bullet_factory;
    std::unique_ptr<SpaceshipController> spaceship;

    std::unique_ptr<AsteroidFactory> asteroid_factory;
    AsteroidBulletCollisionDetector asteroid_bullet_collision_detector;
    ElasticCollisionDetector asteroid_collision_detector;
    std::vector<std::string> asteroid_material_paths;

    std::unique_ptr<HUDProperties> spaceship_point_props;
    std::unique_ptr<HUD> spaceship_points;
};

#endif// ASTEROIDS_GAME_HPP