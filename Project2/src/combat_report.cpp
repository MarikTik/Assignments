#include "combat_report.h"
 
combat_report::combat_report(size_t bots, float boss_power, uint32_t micro_missiles, float defense_matrix_power) 
    :  bots(bots), boss_power(boss_power), micro_missiles(micro_missiles), defense_matrix_power(defense_matrix_power)
{
}

std::ostream& operator << (std::ostream& os, combat_report& report)
{   
    os << "D.Va's Combat Report\n"
       << "Combat with " << report.bots << " enemy bots and one enemy boss with power " << report.boss_power << ".\n"
       << "Loaded mech with 10 micro missiles and the defense matrix with power " << report.defense_matrix_power << ".\n"
       << "Ready for combat!";

    return os;
}

 
