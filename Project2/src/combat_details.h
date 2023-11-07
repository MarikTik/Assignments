#ifndef COMBAT_DETAILS_H_
#define COMBAT_DETAILS_H_

#include <stdint.h>
#include <cstddef>
#include <ostream>
 

#include "combat_report.h"

class combat_details{
    public:
        combat_details();
        ~combat_details();
         
        friend std::istream& operator >> (std::istream& is, combat_details& details);
        combat_report create_report();
    private:
        size_t botsCount;
        uint32_t* botsPower = NULL;
        float bossPower;
        uint32_t microMissiles;
        float defenseMatrix;
};

#endif