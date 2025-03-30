#include "planning_module.h"

Planning_Module::Planning_Module()
{
}

/// @brief Plans the path of the robot for exploration
/// @param pose_hat estimated current position of robot
/// @param contact_data contact sensor measurements at current position
void Planning_Module::plan_path_exploration(const Pose &pose_hat, const std::array<bool, 4> &contact_data)
{
    planned_path.clear();

    // Find all open directions
    std::vector<int> open_directions;
    for (int i=0; i<contact_data.size(); i++){
        if (!contact_data[i]){
            open_directions.push_back(i);
        }
    }

    // randomly choose a direction
    int direction;
    std::sample(open_directions.begin(), open_directions.end(), &direction, 1, std::mt19937 {std::random_device{}()});

    // set path
    Pose pose_next = pose_hat;
    if (direction == 0){
        pose_next.x += 1;
    } else if (direction == 1){
        pose_next.y += 1;
    } else if (direction == 2){
        pose_next.x -= 1;
    } else {
        pose_next.y -= 1;
    }

    planned_path.push_back(pose_next);

}

/// @brief Calculates the motion commands of the robot 
/// @param pose_hat estimated current position of the robot
/// @param pose_desired desired position of the robot
void Planning_Module::calculate_motion_command(const Pose &pose_hat, const Pose &pose_desired)
{
    std::cout << "pose hat: " << pose_hat;
    std::cout << "pose desired: " << pose_desired;
    motion_command = pose_desired - pose_hat;
}
