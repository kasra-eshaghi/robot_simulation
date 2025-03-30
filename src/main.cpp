/*
    This is the main robot simulation script
    GOAL IS TO WRITE BAD CODE AND THEN COME AROUND AND FIX IT ONE ISSUE AT A TIME
        I want to write the code for getting sensor measurements
*/

#include <iostream>
#include <thread>
#include <string>

#include "yaml-cpp/yaml.h"
// #include <SFML/Graphics.hpp>


#include "world.h"
#include "behavior_controller.h"
#include "visualization.h"


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

    // Craete simulated (true) world
    World world_true(config_yaml, "pose_initial", "map");

    // Create behavior controller for robot
    Behavior_Controller bc(config_yaml, "pose_initial_hat", "map_hat");

    // Create visualization class
    Visuals visuals(config_yaml, world_true.map);

    int iteration = 0;
    while (visuals.window.isOpen() and iteration < 100){
        // Visualization
        sf::Event event;
        while (visuals.window.pollEvent(event)){
            if (event.type == sf::Event::Closed){
                visuals.window.close();
            }
        }
        visuals.clear_draw_display(world_true.robot.pose, bc.lm);
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));


        // std::cout << "iteration " << iteration << std::endl;
        // std::cout << "true pose: " << world_true.robot.pose;
        
        // Get sensor measurements 
        world_true.robot.get_contact_data(world_true.map);

        // std::cout << "contact data: ";
        // world_true.robot.print_contact_data();

        // Give sensor measurements to behavior controller and get motion commands
        Pose command = bc.determine_next_command(world_true.robot.contact_data);

        // std::cout << "command:" << command; 

        // // Execute motion commands of robot
        world_true.robot.execute_motion_commands(command);

        ++iteration;


    }



    return 0;
}





    // // while (visuals.window.isOpen()){
    // //     sf::Event event;
    // //     while (visuals.window.pollEvent(event)){
    // //         if (event.type == sf::Event::Closed){
    // //             visuals.window.close();
    // //         }
    // //     }

    // //     // display window
    // //     visuals.clear_draw_display(simulator.pose_true);

    // //     // get sensor measurements
    // //     simulator.get_sensor_data();

    // //     // calculate and execute motion commands
    // //     int command = robot.calculate_motion_command(simulator.proximity_measurements);
    // //     simulator.execute_motion_command(command);

    // //     std::cout << "Proximity measurements: " << simulator.proximity_measurements << std::endl;
    // //     std::cout << "Command: " << command << std::endl;

    // //     // Pause
    // //     std::this_thread::sleep_for(std::chrono::milliseconds(visuals.frame_rate));

    // // }