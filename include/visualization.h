#ifndef VISUALIZATION_H
#define VISUALIZATION_H

#include "yaml-cpp/yaml.h"
#include <SFML/Graphics.hpp>

#include "data_types.h"
#include "localization_module.h"

#include <map>

class Visuals{
    public:
        Visuals(const YAML::Node& config_yaml, const Map& map_true);


        sf::Color free_space_color, obstacle_space_color, robot_body_color, pose_hat_sample_color;
        int cell_size, frame_rate;

        sf::RenderWindow window;
        sf::RenderTexture background_texture;
        sf::Sprite background_sprite; 
        sf::RectangleShape robot_shape, obstacle_shape;
        sf::CircleShape pose_hat_sample_shape;

        void clear_draw_display(const Pose& pose, const Localization_Module& lm);


    private:


        std::map<std::string, sf::Color> color_map = {
            {"White", sf::Color::White},
            {"Black", sf::Color::Black},
            {"Red", sf::Color::Red},
            {"Green", sf::Color::Green},
            {"Blue", sf::Color::Blue},
            {"Yellow", sf::Color::Yellow},
            {"Magenta", sf::Color::Magenta},
            {"Cyan", sf::Color::Cyan},
        };  

        void create_background_sprite(const Map& map_true);
        void create_shapes();
};


#endif //VISUALIZATION_H
