#include "data_types.h"

void Pose::set_values(int x_, int y_)
{
    x = x_;
    y = y_;
}

Pose Pose::operator+(const Pose &another_pose) const
{
    Pose pose_sum;
    pose_sum.x = x + another_pose.x;
    pose_sum.y = y + another_pose.y;

    return pose_sum;
}

Pose Pose::operator-(const Pose &another_pose) const
{
    Pose pose_subtract;
    pose_subtract.x = x - another_pose.x;
    pose_subtract.y = y - another_pose.y;

    return pose_subtract;
}

std::ostream &operator<<(std::ostream &os, Pose pose)
{
    os << "(x: " << pose.x << ", y: " << pose.y << ")" << std::endl;
    return os;
}

Map::Map() {
}

Map::Map(const std::vector<std::vector<int>> &map_data){
    data = map_data;
}

Map::Map(const YAML::Node &config_yaml, const std::string &map_data_name){  
    data.clear();
    create(config_yaml, map_data_name);
}

void Map::create(const YAML::Node &config_yaml, const std::string &map_data_name){
    // Read map file
    std::string map_file_name = config_yaml[map_data_name].as<std::string>();
    std::ifstream map_file(map_file_name);
    if (!map_file.is_open()){
        throw std::invalid_argument("Unable to open map file");
    }

    
    // Create map 
    int n_columns_created = 0;
    std::string csv_file_row;
    while (std::getline(map_file, csv_file_row)){
        std::stringstream csv_file_row_ss(csv_file_row);
        std::string occupancy;

        int column_number = 0;
        while (std::getline(csv_file_row_ss, occupancy, ',')){
            if (column_number >= n_columns_created){
                // add new column
                std::vector<int> temp_data = {std::stoi(occupancy)};
                data.push_back(temp_data);
                n_columns_created += 1;
            } else {
                data[column_number].push_back(std::stoi(occupancy));
            }
            column_number += 1;
        }
    }

    n_columns = data.size();
    n_rows = data[0].size(); 
}

std::ostream &operator<<(std::ostream &os, Map map)
{
    os << "Data: " << std::endl;
    for (int y = 0; y < map.data[0].size(); ++y){
        for (int x = 0; x < map.data[0].size(); ++x){
            std::cout << map.data[x][y] << " ";
        }
        std::cout << std::endl;
    }
    os << map.n_columns << " columns, " << map.n_rows << " rows" << std::endl;

    return os;
}


