/*
    This is the main robot simulation script
    GOAL IS TO WRITE BAD CODE AND THEN COME AROUND AND FIX IT ONE ISSUE AT A TIME
        I want to write the code for getting sensor measurements
*/

#include <iostream>
#include <thread>

#include "yaml-cpp/yaml.h"
#include <SFML/Graphics.hpp>

#include "simulator.h"
#include "robot.h"

int main(int argc, char* argv[]){

    // Read input configuration file
    std::string config_file_name;
    YAML::Node config_yaml;
    if (argc == 1){
        std::cout << "params file not provided!" << std::endl; 
        return -1;
    } else {
        config_file_name = argv[1];
        std::cout << "Read config file name: " << config_file_name << std::endl;
        config_yaml = YAML::LoadFile(config_file_name);
    }
    
    // Create simulator class
    Simulator simulator(config_yaml);

    std::cout << "Simulator" << std::endl;
    std::cout << "Pose: " << simulator.pose_true << std::endl;
    std::cout << "Map: " << std::endl;
    std::cout << simulator.map_true << std::endl;

    // Create robot class
    Robot robot(config_yaml);
    std::cout << "Robot" << std::endl;
    std::cout << "Pose pickup: " << robot.pose_pickup << std::endl;
    std::cout << "Pose dropoff: " << robot.pose_dropoff << std::endl;
    std::cout << "Map: " << std::endl;
    std::cout << robot.map_hat << std::endl;


    // std::cout << "Initial pose: " << simulator.pose_true << std::endl;

    // // get sensor measurements
    // simulator.get_sensor_data();
    // std::cout << "Proximity measurements: " << simulator.proximity_measurements << std::endl;

    // // calculate motion commands
    // int command = robot.calculate_motion_command(simulator.proximity_measurements);
    // command = 3;
    // std::cout << "Command: " << command << std::endl;

    // // execute motion command
    // simulator.execute_motion_command(command);

    // // print updated pose
    // std::cout << "New pose: " << simulator.pose_true << std::endl;

    // // get sensor measurements
    // simulator.get_sensor_data();
    // std::cout << "New proximity measurements: " << simulator.proximity_measurements << std::endl;




    // create window
    int cell_size = 100;
    int width = simulator.map_true.n_columns * cell_size;
    int height = simulator.map_true.n_rows * cell_size;
    sf::RenderWindow window(sf::VideoMode(width, height), "Robot Simulation");

    // create background texture
    sf::RenderTexture background_texture;
    background_texture.create(width, height);
    background_texture.clear(sf::Color::White);
    for (int row_num = 0; row_num < simulator.map_true.n_rows; row_num++){
        for (int column_num = 0; column_num < simulator.map_true.n_columns; column_num++){
            sf::RectangleShape obstacle(sf::Vector2f(cell_size, cell_size));
            obstacle.setPosition((row_num)*cell_size, column_num*cell_size);
            if (simulator.map_true.data[column_num][row_num]){
                obstacle.setFillColor(sf::Color::Black);
            } else {
                obstacle.setFillColor(sf::Color::White);
            }
            background_texture.draw(obstacle);
        }
    }
    background_texture.display();

    // create background sprite out of texture
    sf::Sprite background_sprite(background_texture.getTexture());

    // Create robot shape
    sf::RectangleShape robot_shape(sf::Vector2f(cell_size, cell_size));
    robot_shape.setFillColor(sf::Color::Red);

    // Create robot direction shape
    sf::RectangleShape direction_shape(sf::Vector2f(cell_size / 2, 10));
    direction_shape.setFillColor(sf::Color::Blue);


    while (window.isOpen()){
        sf::Event event;
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed){
                window.close();
            }
        }
        // Clear window
        window.clear();

        // Draw background
        window.draw(background_sprite);

        // Draw robot
        robot_shape.setPosition(simulator.pose_true.y*cell_size, simulator.pose_true.x*cell_size);
        window.draw(robot_shape);

        // Draw direction
        direction_shape.setPosition(simulator.pose_true.y*cell_size + cell_size/2, simulator.pose_true.x*cell_size + cell_size/2);
        int angle;
        switch (simulator.pose_true.theta){
            case 0:
                angle = 0;
                break;
            case 1:
                angle = 270;
                break;
            case 2:
                angle = 180;
                break;
            case 3:
                angle = 90;
                break;
        }
        direction_shape.setRotation(angle);
        window.draw(direction_shape);

        // std::cout << simulator.pose_true << std::endl;

        // Display window
        window.display();

        // get sensor measurements
        simulator.get_sensor_data();

        // calculate and execute motion commands
        int command = robot.calculate_motion_command(simulator.proximity_measurements);
        simulator.execute_motion_command(command);

        std::cout << "Proximity measurements: " << simulator.proximity_measurements << std::endl;
        std::cout << "Command: " << command << std::endl;

        // Pause
        std::this_thread::sleep_for(std::chrono::seconds(1));


    }
    


    return 0;
}