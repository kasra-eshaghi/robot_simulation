#ifndef COORDINATOR_H
#define COORDINATOR_H

#include <iostream>
#include <string>
#include <fstream>

#include "yaml-cpp/yaml.h"
#include "simulator.h"
#include "robot.h"

class Coordinator{

    public:
        Coordinator(std::string config_file);
        Simulator simulator;
        // Robot robot;

        void print_problem_config();

    private:
        std::vector<std::vector<int>> get_map_data(std::ifstream& csv_file);
        Pose get_pose_data(const YAML::Node& config_yaml, const std::string& pose_name);
};

#endif