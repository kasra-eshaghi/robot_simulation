#ifndef WORLD_H
#define WORLD_H

#include "yaml-cpp/yaml.h"

#include "data_types.h"
#include "robot.h"
#include "helper_functions.h"


class World {
    public:
        Robot robot;
        Map map;

        World();
        World(const YAML::Node& config_yaml, const std::string& pose_init_name, const std::string& map_data_name);
        void create(const YAML::Node& config_yaml, const std::string& pose_init_name, const std::string& map_data_name);

    private:

};

#endif //WORLD_H