#include "data_types.h"

Map get_map_data(const YAML::Node& config_yaml){
    Map map;
    
    std::string map_file_name = config_yaml["problem"]["map"].as<std::string>();
    std::ifstream map_file(map_file_name);
    if (!map_file.is_open()){
        throw std::invalid_argument("Unable to open map file");
    }

    std::vector<int> map_row;
    std::string csv_file_row;
    while (std::getline(map_file, csv_file_row)){
        
        std::stringstream csv_file_row_ss(csv_file_row);
        std::string occupancy;
        while (std::getline(csv_file_row_ss, occupancy, ',')){
            map_row.push_back(std::stoi(occupancy));
        }
        map.data.push_back(map_row);
        map_row.clear();
    }

    map.n_rows = map.data.size();
    map.n_columns = map.data[0].size();

    return map; 
}

Pose get_pose_data(const YAML::Node& config_yaml, const std::string& pose_name){
    Pose pose;
    pose.x =  config_yaml["problem"][pose_name][0].as<int>();
    pose.y =  config_yaml["problem"][pose_name][1].as<int>();
    pose.theta = config_yaml["problem"][pose_name][2].as<int>();

    // make sure pose isn't in occupied area of map
    Map map_temp = get_map_data(config_yaml);
    if (check_occupancy(map_temp, pose)){
        throw std::invalid_argument(pose_name + " in occupied area");
    } 
    // make sure pose theta makes sense
    if (pose.theta < 0 or pose.theta >3){
        throw std::invalid_argument(pose_name + " has invalid orientation");
    };

    return pose;
}

bool check_occupancy(Map& map, Pose& pose){
    // checks the occupancy of a pose within a map
    if (pose.x >= map.n_rows or pose.x < 0 or pose.y >= map.n_columns or pose.y < 0){
        return true;
    } else {
        return map.data[pose.x][pose.y];
    }
}