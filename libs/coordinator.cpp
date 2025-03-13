#include "coordinator.h"

Coordinator::Coordinator(std::string config_file){
    std::cout << "Creating problem..." << std::endl;

    // create simulator and robot classes
    // simulator = Simulator();
    // robot = Robot();

    // load config yaml file
    YAML::Node config_yaml = YAML::LoadFile(config_file);

    // get map
    std::string csv_file_name = config_yaml["problem"]["map"].as<std::string>();
    std::ifstream csv_file(csv_file_name);
    if (!csv_file.is_open()){
        std::cerr << "Failed to open file" << std::endl;
        throw std::invalid_argument("csv file invalid!");
    }
    std::vector<std::vector<int>> map_true = get_map_data(csv_file);
    Pose pose_true = get_pose_data(config_yaml, "initial_pose");
    simulator = Simulator(map_true, pose_true);
    // simulator.map_true = get_map_data(csv_file);

    // // get poses
    // simulator.pose_true = get_pose_data(config_yaml, "initial_pose");
    // robot.pose_pickup = get_pose_data(config_yaml, "pickup_pose");
    // robot.pose_dropoff = get_pose_data(config_yaml, "dropoff_pose");
}

std::vector<std::vector<int>> Coordinator::get_map_data(std::ifstream& csv_file){
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

Pose Coordinator::get_pose_data(const YAML::Node& config_yaml, const std::string& pose_name){
    Pose pose;
    pose.x =  config_yaml["problem"][pose_name][0].as<int>();
    pose.y =  config_yaml["problem"][pose_name][1].as<int>();
    pose.theta = config_yaml["problem"][pose_name][2].as<int>();

    // check feasibility of pose
    int n_map_rows = simulator.map_true.size();
    int n_map_columns = simulator.map_true[0].size();
    if (pose.x >= n_map_rows or pose.x < 0 or pose.y >= n_map_columns or pose.y < 0){
        throw std::invalid_argument(pose_name  + " not in map!");
    }
    if (simulator.map_true[pose.x][pose.y] == 1){
        throw std::invalid_argument(pose_name + " not free!");
    }

    return pose;
}

void Coordinator::print_problem_config(){
    std::cout << "Map:" << std::endl;
    for (auto &map_row : simulator.map_true){
        for (int occ : map_row){
            std::cout << occ << ", ";
        }
        std::cout << std::endl;
    }

    std::cout << "Initial pose: (" << simulator.pose_true.x << ", " << simulator.pose_true.y << ", " << simulator.pose_true.theta << ")\n";
    std::cout << "Pickup pose: (" << robot.pose_pickup.x << ", " << robot.pose_pickup.y << ", " << robot.pose_pickup.theta << ")\n";
    std::cout << "Dropoff pose: (" << robot.pose_dropoff.x << ", " << robot.pose_dropoff.y << ", " << robot.pose_dropoff.theta << ")\n";

}