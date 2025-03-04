
#include "problem_description.h"


Problem::Problem(const std::string& config_file_name){
    std::cout << "Creating problem..." << std::endl;
    // load config yaml file
    YAML::Node config_yaml = YAML::LoadFile(config_file_name);

    // get map
    std::string csv_file_name = config_yaml["problem"]["map"].as<std::string>();
    std::ifstream csv_file(csv_file_name);
    if (!csv_file.is_open()){
        std::cerr << "Failed to open file" << std::endl;
        throw std::invalid_argument("csv file invalid!");
    }
    map = get_map_data(csv_file);

    // get poses
    initial_pose = get_pose_data(config_yaml, "initial_pose");
    pickup_pose = get_pose_data(config_yaml, "pickup_pose");
    dropoff_pose = get_pose_data(config_yaml, "dropoff_pose");
}

void Problem::print_problem_config(){
    std::cout << "Map:" << std::endl;
    for (auto &map_row : map){
        for (int occ : map_row){
            std::cout << occ << ", ";
        }
        std::cout << std::endl;
    }

    std::cout << "Initial pose: (" << initial_pose.x << ", " << initial_pose.y << ", " << initial_pose.theta << ")\n";
    std::cout << "Pickup pose: (" << pickup_pose.x << ", " << pickup_pose.y << ", " << pickup_pose.theta << ")\n";
    std::cout << "Dropoff pose: (" << dropoff_pose.x << ", " << dropoff_pose.y << ", " << dropoff_pose.theta << ")\n";

}

std::vector<std::vector<int>> Problem::get_map_data(std::ifstream& csv_file){
    std::vector<std::vector<int>> map;
    std::vector<int> map_row;
    std::string csv_file_row;
    while (std::getline(csv_file, csv_file_row)){
        
        std::stringstream csv_file_row_ss(csv_file_row);
        std::string occupancy;
        while (std::getline(csv_file_row_ss, occupancy, ',')){
            map_row.push_back(std::stoi(occupancy));
        }
        map.push_back(map_row);
        map_row.clear();
    }

    return map;
}

Pose Problem::get_pose_data(const YAML::Node& config_yaml, const std::string& pose_name){
    Pose pose;
    pose.x =  config_yaml["problem"][pose_name][0].as<int>();
    pose.y =  config_yaml["problem"][pose_name][1].as<int>();
    pose.theta = config_yaml["problem"][pose_name][2].as<int>();

    // check feasibility of pose
    int n_rows = map.size();
    int n_columns = map[0].size();
    if (pose.x >= n_rows or pose.x < 0 or pose.y >= n_columns or pose.y < 0){
        throw std::invalid_argument(pose_name  + " not in map!");
    }
    if (map[pose.x][pose.y] == 1){
        throw std::invalid_argument(pose_name + " not free!");
    }

    return pose;
}

// void Problem::check_pose_data(){
//     int n_rows = map.size();
//     int n_columns = map[0].size();

//     // Check if poses are within map
//     if (initial_pose.x >= n_rows or initial_pose.x < 0 or initial_pose.y >= n_columns or initial_pose.y < 0){
//         throw std::invalid_argument("Initial pose not in map!");
//     }
//     if (pickup_pose.x >= n_rows or pickup_pose.x < 0 or pickup_pose.y >= n_columns or pickup_pose.y < 0){
//         throw std::invalid_argument("Pickup pose not in map!");
//     }
//     if (dropoff_pose.x >= n_rows or dropoff_pose.x < 0 or dropoff_pose.y >= n_columns or dropoff_pose.y < 0){
//         throw std::invalid_argument("Dropoff pose not in map!");
//     }

//     // Check if poses are in open space
//     if (map[initial_pose.x][initial_pose.y] == 1){
//         throw std::invalid_argument("Initial pose not free!");
//     }
//     if (map[pickup_pose.x][pickup_pose.y] == 1){
//         throw std::invalid_argument("Pickup pose not free!");
//     }
//     if (map[dropoff_pose.x][dropoff_pose.y] == 1){
//         throw std::invalid_argument("Dropoff pose not free!");
//     }

//     return;
// }
