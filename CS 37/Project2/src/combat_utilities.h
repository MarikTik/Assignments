#ifndef COMBAT_UTILITIS_H_
#define COMBAT_UTILITIES_H_
 
#include <stdint.h>
#include <cstddef>

template<typename T>
T single_missile_power(T arg){
    if (arg <= 15)
        return arg * 2;
    return arg * 5;
}

 void load_dva(float matrix_power_required, float& defense_matrix); // Load Defense Matrix 
 void load_dva(uint32_t& micro_missiles, float missile_power_required); // Load Micro Missiles 
 float matrix_power(uint32_t* bots_power, size_t bots_number, float boss_power);  

#endif