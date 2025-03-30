#ifndef BEHAVIOR_CONTROLLER_H
#define BEHAVIOR_CONTROLLER_H

#include <array>

#include "yaml-cpp/yaml.h"

#include "planning_module.h"
#include "localization_module.h"
#include "world.h"

class Behavior_Controller {

    public:
        Localization_Module lm;
        Planning_Module pm;
        World world_hat; 

        std::string status = "localizing";
        std::map<std::string, int> behavior_map = {
            {"localizing", 1},
            {"moving_to_target", 2},
        };

        bool mission_complete = false;

        Behavior_Controller();
        Behavior_Controller(YAML::Node& config_yaml, const std::string& pose_init_hat_name, const std::string& map_data_name);

        Pose determine_next_command(std::array<bool, 4> contact_data);

    private:

};


#endif//BEHAVIOR_CONTROLLER_H