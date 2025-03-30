#ifndef ROBOTICS_H
#define ROBOTICS_H

#include "data_types.h"
#include "environment.h"

class Localization{
    Pose pose_hat;
    std::vector<Pose> pose_hat_samples;
    std::string status;

    Localization(Map& map);
    void update_samples(const Contact_Data& data);

};

class Planning{
    std::vector<Pose> route;
    Motion_Command command;
    
    void plan_route_exploration(const Pose& pose_hat, const Contact_Data& data);
    void plan_route_destination(const Pose& pose_hat, const Pose& destination);
    void calculate_command(const Pose& pose_hat, const Pose& pose_next); 

};

class Behavior_Tree{

};




#endif //ROBOTICS_H