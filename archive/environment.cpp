// #include "environment.h"


void Contact_Sensor::get_data(const Map &map, const Pose &pose){

    // get sensor measurements assuming robot is oriented with map
    for (int i=0; i < data.size(); i++){
        Pose pose_temp = pose;
        if (i == 0){
            pose_temp.x += 1;
        } else if (i == 1){
            pose_temp.y +=1;
        } else if (i == 2){
            pose_temp.x -= 1;
        } else {
            pose_temp.y -= 1;
        }
        data[i] = check_occupancy(map, pose_temp);
    }

    // rotate measurements
    std::rotate(data.begin(), data.begin() + pose.theta, data.end());
}

