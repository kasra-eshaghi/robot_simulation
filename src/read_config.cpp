// This file is used to read the configuration file, in yaml format
#include <iostream>
#include <fstream>

#include <vector>


#include "yaml-cpp/yaml.h"

#include "problem_description.h"

class Robot{
    public:
        Robot(Pose pose_true);
};



int main(int argc, char* argv[]){

    // get problem
    std::string config_file_name = "problem.yaml";
    Problem problem(config_file_name);
    problem.print_problem_config();



    return 0;
}

