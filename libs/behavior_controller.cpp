#include "behavior_controller.h"

Behavior_Controller::Behavior_Controller()
{
    lm.localized = false;
    lm.initialize_localization(world_hat.map);
}

Behavior_Controller::Behavior_Controller(YAML::Node& config_yaml, const std::string& pose_init_hat_name, const std::string& map_data_name)
{
    world_hat.create(config_yaml,pose_init_hat_name, map_data_name);
    lm.localized = false;
    lm.initialize_localization(world_hat.map);
}

Pose Behavior_Controller::determine_next_command(std::array<bool, 4> contact_data)
{
    Pose motion_command;

    switch(behavior_map[status]){
        case 1: // "localizing"
            // Update localization
            lm.update_samples(contact_data, world_hat);

            // If localization is complete, don't move and update status.
            // Otherwise, calculate motion commands to explore
            if (lm.localized){
                motion_command.set_values(0, 0);
                status = "moving_to_target";
            } else {
                Pose pose_hat(0, 0);
                pm.plan_path_exploration(pose_hat, contact_data);
                pm.calculate_motion_command(pose_hat, pm.planned_path[0]);

                motion_command = pm.motion_command;

                // move samples based on calculated motion commands
                lm.move_samples(motion_command);
            }
            break;
        case 2: //"moving_to_target"
            // Plan path if needed

            std::cout << "Estimated position: " << lm.pose_hat;
            
            break;
    }



    return motion_command;
}
