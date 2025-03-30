#ifndef LOCALIZATION_MODULE_H
#define LOCALIZATION_MODULE_H

#include "data_types.h"
#include "world.h"


/// @brief Localization module containing necessary functions for localizing robot in a known map

class Localization_Module{

    public:
    
        Pose pose_hat;
        std::vector<Pose> pose_hat_samples;
        bool localized = false; //indicates whether robot is localized

        Localization_Module();
        Localization_Module(const Map& map_hat);

        void initialize_localization(const Map& map_hat);
        void update_samples(const std::array<bool, 4> contact_data, World world_hat);
        void move_samples(const Pose& motion_command);

    private:    

};



#endif //LOCALIZATION_MODULE_H