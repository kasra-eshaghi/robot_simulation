#include "world.h"

World::World(){}

World::World(const YAML::Node& config_yaml, const std::string& pose_init_name, const std::string& map_data_name){
    create(config_yaml, pose_init_name, map_data_name);
}

void World::create(const YAML::Node &config_yaml, const std::string &pose_init_name, const std::string &map_data_name)
{
    robot.create(config_yaml, pose_init_name);
    map.create(config_yaml, map_data_name);

    if (check_occupancy(map, robot.pose)){
        throw std::invalid_argument("Robot not in feasible position");
    }

}
