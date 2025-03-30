#ifndef PLANNING_MODULE_H
#define PLANNING_MODULE_H

#include <vector>
#include <random>

#include "data_types.h"

class Planning_Module {
    public:
        std::vector<Pose> planned_path;
        Pose motion_command;

        Planning_Module();

        void plan_path_exploration(const Pose& pose_hat, const std::array<bool, 4>& contact_data);
        void calculate_motion_command(const Pose& pose_hat, const Pose& pose_desired);

    private:
};


#endif //PLANNING_MODULE_H