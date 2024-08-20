#include "combat_utilities.h"
#include <cmath>

void load_dva(float matrix_power_required, float& defense_matrix){
    if (defense_matrix < matrix_power_required)
        defense_matrix = matrix_power_required;
}
void load_dva(uint32_t& micro_missiles, float missile_power_required){
    micro_missiles = std::ceil(missile_power_required / 60);
}

float matrix_power(uint32_t *bots_power, size_t bots_number, float boss_power)
{
    float total_damage = 0;
    for(auto i = 0; i < bots_number; i++)
        total_damage += bots_power[i];
    total_damage += boss_power;
    return total_damage;
}
