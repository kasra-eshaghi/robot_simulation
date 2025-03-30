#ifndef HELPER_FUNCTIONS_H
#define HELPER_FUNCTIONS_H
/*
    This library is used to define the various data types and the functions used to read data from config files
*/

#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

#include "yaml-cpp/yaml.h"

#include "data_types.h"


// USED
bool check_occupancy(const Map& map, const Pose& pose);

#endif // HELPER_FUNCTIONS_H