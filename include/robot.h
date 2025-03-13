#ifndef ROBOT_H
#define ROBOT_H

#include <string>
#include <random>

#include "data_types.h"


class Robot {
    public:
        Robot(YAML::Node& config_yaml);

        Map map_hat;
        Pose pose_hat, pose_pickup, pose_dropoff; 
        std::string status;

        int calculate_motion_command(Proximity_measurements& measurements);

};

#endif