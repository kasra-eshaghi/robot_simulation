#include "visualization.h"

Visuals::Visuals(const YAML::Node& config_yaml, const Map& map_true){

    // Get parameters
    cell_size = config_yaml["graphics"]["cell_size"].as<int>();
    frame_rate = config_yaml["graphics"]["frame_rate"].as<int>();
    free_space_color = color_map[config_yaml["graphics"]["free_space_color"].as<std::string>()];
    obstacle_space_color = color_map[config_yaml["graphics"]["obstacle_space_color"].as<std::string>()];
    robot_body_color = color_map[config_yaml["graphics"]["robot_body_color"].as<std::string>()];
    pose_hat_sample_color = color_map[config_yaml["graphics"]["pose_hat_sample_color"].as<std::string>()];

    // Create window, background, and shapes
    window.create(sf::VideoMode({static_cast<unsigned int>(cell_size*map_true.n_columns), static_cast<unsigned int>(cell_size*map_true.n_rows)}), "Robot Simulation");
    create_background_sprite(map_true);
    create_shapes();


}

void Visuals::create_background_sprite(const Map& map_true){
    // Creates background for environment
    background_texture.create(map_true.n_columns*cell_size, map_true.n_rows*cell_size);
    background_texture.clear(free_space_color);

    obstacle_shape.setSize(sf::Vector2f(cell_size, cell_size));
    for (int row_num = 0; row_num < map_true.n_rows; row_num++){
        for (int column_num = 0; column_num < map_true.n_columns; column_num++){
            obstacle_shape.setPosition(column_num*cell_size, row_num*cell_size);
            if (map_true.data[column_num][row_num]){
                obstacle_shape.setFillColor(obstacle_space_color);
            } else {
                obstacle_shape.setFillColor(free_space_color);
            }
            background_texture.draw(obstacle_shape);
        }
    }
    background_texture.display();
    background_sprite.setTexture(background_texture.getTexture());
}

void Visuals::create_shapes(){
    // Creates necessary shapes
    robot_shape.setSize(sf::Vector2f(cell_size, cell_size));
    robot_shape.setFillColor(robot_body_color);

    pose_hat_sample_shape.setRadius(cell_size/4);
    pose_hat_sample_shape.setFillColor(pose_hat_sample_color);
}

void Visuals::clear_draw_display(const Pose& pose, const Localization_Module& lm){
    window.clear();
    window.draw(background_sprite);

    robot_shape.setPosition(pose.x*cell_size, pose.y*cell_size);
    window.draw(robot_shape);

    for (int i = 0; i<lm.pose_hat_samples.size(); ++i){
        pose_hat_sample_shape.setPosition(lm.pose_hat_samples[i].x*cell_size, lm.pose_hat_samples[i].y*cell_size);
        window.draw(pose_hat_sample_shape);
    }

    


    // Display window
    window.display();

}
