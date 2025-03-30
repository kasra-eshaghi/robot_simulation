#include "robot.h"

Robot::Robot(){

}

Robot::Robot(const Pose& pose_init){
    pose = pose_init;
}

Robot::Robot(const YAML::Node &config_yaml, const std::string &pose_init_name){
    create(config_yaml, pose_init_name);
}

void Robot::create(const YAML::Node &config_yaml, const std::string &pose_init_name){
    
    pose.x =  config_yaml[pose_init_name][0].as<int>();
    pose.y =  config_yaml[pose_init_name][1].as<int>();
}

void Robot::get_contact_data(const Map& map){
        // get sensor measurements assuming robot is oriented with map
        for (int i=0; i < contact_data.size(); i++){
            Pose pose_temp = pose;
            if (i == 0){
                pose_temp.x += 1;
            } else if (i == 1){
                pose_temp.y +=1;
            } else if (i == 2){
                pose_temp.x -= 1;
            } else {
                pose_temp.y -= 1;
            }
            contact_data[i] = check_occupancy(map, pose_temp);
        }
    
        // // rotate measurements
        // std::rotate(contact_data.begin(), contact_data.begin() + pose.theta, contact_data.end());
    
}

/// @brief Executes the motion commands of the robot by updating the true pose of the robot
/// @param motion_command motion command (delta pose)
void Robot::execute_motion_commands(const Pose &motion_command)
{
    pose = pose + motion_command;
}
