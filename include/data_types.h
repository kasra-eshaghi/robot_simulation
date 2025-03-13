#ifndef DATA_TYPES_H
#define DATA_TYPES_H
/*
    This library is used to define the various data types and the functions used to read data from config files
*/

#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

#include "yaml-cpp/yaml.h"


// Data types
// typedef std::vector<std::vector<int>> Map;

struct Map{
    int n_rows;
    int n_columns;
    std::vector<std::vector<int>> data;


    friend std::ostream& operator << (std::ostream& os, const Map& map){
        for (auto data_row:map.data){
            for (auto occ:data_row){
                os << occ << " ";
            }
            os << std::endl;
        }
        return os;
    }

};

struct Pose{
    int x;
    int y;
    int theta;

    friend std::ostream& operator << (std::ostream& os, const Pose& pose){
        os << "(x: " << pose.x << ", y: " << pose.y << ", theta: " << pose.theta << ")";
        return os;
    }
};

struct Proximity_measurements{
    std::array<bool, 4> data;
    friend std::ostream& operator << (std::ostream& os, const Proximity_measurements& proximity_measurements){
        os << "( ";
        for (bool value : proximity_measurements.data){
            os << value << " ";
        }
        os << ")";

        return os;
    }
};

// Data reading functions
Map get_map_data(const YAML::Node& config_yaml);
Pose get_pose_data(const YAML::Node& config_yaml, const std::string& pose_name);
bool check_occupancy(Map& map, Pose& pose);

#endif // DATA_TYPES_H