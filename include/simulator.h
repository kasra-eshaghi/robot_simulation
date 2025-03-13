#ifndef SIMULATOR_H
#define SIMULATOR_H

#include "data_types.h"
#include <array>
#include <iostream>

#include "yaml-cpp/yaml.h"
#include <fstream>


class Simulator {

    public:
        Simulator(YAML::Node& config_yaml);
        Map map_true;
        Pose pose_true;
        Proximity_measurements proximity_measurements;

        void get_sensor_data();
        void execute_motion_command(int motion_command);
    //     void print_sensor_data();
        




};


#endif