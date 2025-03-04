#ifndef PROBLEM_DESCRIPTION_H
#define PROBLEM_DESCRIPTION_H

#include <vector>
#include <iostream>
#include <fstream>

#include "yaml-cpp/yaml.h"
#include "data_types.h"


struct Config {
    std::vector<std::vector<int>> map;

    Pose initial_pose;
    Pose pickup_pose;
    Pose dropoff_pose;
};

class Problem {
    public:
        std::vector<std::vector<int>> map;
        Pose initial_pose;
        Pose pickup_pose;
        Pose dropoff_pose;
        // Config problem_config;
        Problem(const std::string& config_file_name);
        void print_problem_config();

    private:
        std::vector<std::vector<int>> get_map_data(std::ifstream& csv_file);
        Pose get_pose_data(const YAML::Node& config_yaml, const std::string& pose_name);
        // void check_pose_data();

};



#endif // PROBLEM_DESCRIPTION_H