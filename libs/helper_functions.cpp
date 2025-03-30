#include "helper_functions.h"

bool check_occupancy(const Map& map, const Pose& pose){
    // checks the occupancy of a pose within a map
    if (pose.x >= map.n_columns or pose.x < 0 or pose.y >= map.n_rows or pose.y < 0){
        return true;
    } else {
        return map.data[pose.x][pose.y];
    }
}