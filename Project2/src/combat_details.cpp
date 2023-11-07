#include "combat_details.h"
#include "combat_utilities.h"

#include <fstream>
#include <iomanip>
 
combat_details::combat_details()
{
}

std::istream& operator >> (std::istream& is, combat_details& details){
    is >> details.botsCount;
    if (details.botsCount)
        details.botsPower = new uint32_t[details.botsCount];
    for (auto i = 0; i < details.botsCount; i++)
        is >> details.botsPower[i];
    is >> details.bossPower >> details.microMissiles >> details.defenseMatrix;
}
 
combat_details::~combat_details(){
    delete[] botsPower;
}

combat_report combat_details::create_report()
{
    float matrixPowerRequired = matrix_power(botsPower, botsCount, bossPower);
    float missilePowerRequired = 0;

    for (auto i = 0; i < botsCount; i++)
        missilePowerRequired += single_missile_power(botsPower[i]);
    missilePowerRequired += single_missile_power(bossPower);

    load_dva(matrixPowerRequired, defenseMatrix);
    load_dva(microMissiles, missilePowerRequired);

    return combat_report(botsCount, bossPower, microMissiles, defenseMatrix);
}

 
