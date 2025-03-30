#ifndef ROBOT_H
#define ROBOT_H

#include <string>
#include <array>

#include "yaml-cpp/yaml.h"

#include "data_types.h"
#include "helper_functions.h"

class Robot {
    public:
        // variables
        Pose pose;
        std::array<bool, 4> contact_data;

        Robot();
        Robot(const Pose& pose_init);
        Robot(const YAML::Node& config_yaml, const std::string& pose_init_name);

        void create(const YAML::Node& config_yaml, const std::string& pose_name);
        void get_contact_data(const Map& map);
        void execute_motion_commands(const Pose& motion_command);

        void print_contact_data(){
            std::cout << "(" << contact_data[0] << ", " << contact_data[1] << ", " << contact_data[2] << ", " << contact_data[3] << ")" << std::endl;

        }


};

// std::ostream &operator<<(std::ostream &os, std::array<bool, 4> contact_data)
// {
//     os << "(" << contact_data[0] << ", " << contact_data[1] << ", " << contact_data[2] << ", " << contact_data[3] << ")" << std::endl;
//     return os;
// }

#endif