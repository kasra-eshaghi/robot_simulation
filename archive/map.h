#ifndef MAP_H
#define MAP_H

#include <vector>
#include <fstream>
#include <iostream>

#include "yaml-cpp/yaml.h"


class Map{
    public:
        int n_rows;
        int n_columns;
        std::vector<std::vector<int>> data;

        Map();
        Map(const std::vector<std::vector<int>>& map_data);
        Map(const YAML::Node& config_yaml, const std::string& map_data_name);

        void print_map();
        void create(const YAML::Node& config_yaml, const std::string& map_data_name);


};

#endif //MAP_H