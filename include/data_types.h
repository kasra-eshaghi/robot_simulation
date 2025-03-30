#ifndef DATA_TYPES_H
#define DATA_TYPES_H

#include <iostream>
#include <fstream>
#include <vector>

#include "yaml-cpp/yaml.h"

class Pose{
    public:
        int x;
        int y;

        Pose(): x(0), y(0) {};
        Pose(int x_, int y_): x(x_), y(y_) {};

        void set_values(int x_, int y_);

        Pose operator+ (const Pose& another_pose) const;
        Pose operator- (const Pose& another_pose) const;
};

std::ostream& operator<< (std::ostream& os, Pose pose);

class Map{
    public:
        int n_rows;
        int n_columns;
        std::vector<std::vector<int>> data;

        Map();
        Map(const std::vector<std::vector<int>>& map_data);
        Map(const YAML::Node& config_yaml, const std::string& map_data_name);

        // void print_map();
        void create(const YAML::Node& config_yaml, const std::string& map_data_name);

};

std::ostream& operator<< (std::ostream& os, Map map);

#endif //DATA_TYPES_H