#ifndef COMBAT_REPORT_H_
#define COMBAT_REPORT_H_
#include <ostream>
#include <cstddef>

class combat_report{
    public:
        combat_report(size_t bots, float boss_power, uint32_t micro_missiles, float defense_matrix_power);
        friend std::ostream& operator << (std::ostream& os, combat_report& report);
    private:
        size_t bots;
        float boss_power;
        uint32_t micro_missiles;
        float defense_matrix_power;
};


#endif