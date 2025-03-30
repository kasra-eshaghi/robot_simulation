#include "localization_module.h"

Localization_Module::Localization_Module()
{
}

Localization_Module::Localization_Module(const Map &map_hat)
{
    initialize_localization(map_hat);
}

/// @brief Initializes the sample based localization module
/// @param map_hat Estimated map
void Localization_Module::initialize_localization(const Map &map_hat)
{

    // go through map and initialize samples in all free spaces
    for (int x = 0; x < map_hat.n_columns; ++x){
        for (int y = 0; y < map_hat.n_rows; ++y){
            if (not map_hat.data[x][y]){
                Pose pose_sample(x, y); 
                pose_hat_samples.push_back(pose_sample);
            }
        }
    }
}

/// @brief Updates the samples of the localization module based on contact data
/// @param contact_data Contact data sensor measurements from robot
void Localization_Module::update_samples(const std::array<bool, 4> contact_data, World world_hat)
{
    // update samples
    std::vector<int> samples_to_remove;
    for (int sample_number = 0; sample_number < pose_hat_samples.size(); ++sample_number){
        // update world and simulate sensor measurements
        world_hat.robot.pose = pose_hat_samples[sample_number];
        world_hat.robot.get_contact_data(world_hat.map);

        if (world_hat.robot.contact_data[0] != contact_data[0] or
            world_hat.robot.contact_data[1] != contact_data[1] or
            world_hat.robot.contact_data[2] != contact_data[2] or
            world_hat.robot.contact_data[3] != contact_data[3]){
                samples_to_remove.push_back(sample_number);
            }
    }

    // remove all sample numbers
    for (int i = samples_to_remove.size() - 1; i >= 0; --i){
        pose_hat_samples.erase(pose_hat_samples.begin() + samples_to_remove[i]);
    }

    // check if localization is complete (update localized)
    if (pose_hat_samples.size() == 1){
        localized = true;
        pose_hat = pose_hat_samples[0];
    }
    
}

void Localization_Module::move_samples(const Pose &motion_command)
{
    for (int sample_number = 0; sample_number < pose_hat_samples.size(); ++sample_number){
        pose_hat_samples[sample_number] = pose_hat_samples[sample_number] + motion_command;
    }
}
