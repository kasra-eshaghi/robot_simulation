#include "simulator.h"

Simulator::Simulator(YAML::Node& config_yaml){

    // Get map and pose
    map_true = get_map_data(config_yaml);
    pose_true = get_pose_data(config_yaml, "pose_initial");

}

void Simulator::get_sensor_data(){
    
    // get sensor measurements assuming robot is oriented with map
    for (int i=0; i < proximity_measurements.data.size(); i++){
        Pose pose_temp = pose_true;
        if (i == 0){
            pose_temp.x += 1;
        } else if (i == 1){
            pose_temp.y +=1;
        } else if (i == 2){
            pose_temp.x -= 1;
        } else {
            pose_temp.y -= 1;
        }
        proximity_measurements.data[i] = check_occupancy(map_true, pose_temp);
    }

    // rotate measurements
    std::rotate(proximity_measurements.data.begin(), proximity_measurements.data.begin() + pose_true.theta, proximity_measurements.data.end());


}

void Simulator::execute_motion_command(int motion_command){
    // update orientation
    pose_true.theta += motion_command;
    pose_true.theta = pose_true.theta % 4;

    // update position
    if (pose_true.theta == 0){
        pose_true.x += 1;
    } else if (pose_true.theta == 1){
        pose_true.y += 1;
    } else if (pose_true.theta == 2){
        pose_true.x -= 1;
    } else {
        pose_true.y -= 1;
    }
    

}

