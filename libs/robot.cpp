#include "robot.h"

Robot::Robot(YAML::Node& config_yaml){

    // Get map
    map_hat = get_map_data(config_yaml);

    // Get pose
    pose_pickup = get_pose_data(config_yaml, "pose_pickup");
    pose_dropoff = get_pose_data(config_yaml, "pose_dropoff");

    // Set status to exploration
    status = "exploration";

}

int Robot::calculate_motion_command(Proximity_measurements& measurements){
    // calculates motion commands for robot to randomly move in the environment

    // Find all open directions
    std::vector<int> open_directions;
    for (int i=0; i<4; i++){
        if (!measurements.data[i]){
            open_directions.push_back(i);
        }
    }

    // randomly choose a direction
    int command;
    std::sample(open_directions.begin(), open_directions.end(), &command, 1, std::mt19937 {std::random_device{}()});

    return command;

}