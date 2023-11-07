#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <ostream>
#include <cstddef>


/*

The code itself is pretty self explanatory so there is not much commenting

*/
 

template<typename T>
T single_missile_power(T arg){
    if (arg <= 15)
        return arg * 2;
    return arg * 5;
}

void load_dva(float matrix_power_required, float& defense_matrix){
    if (defense_matrix < matrix_power_required)
        defense_matrix = matrix_power_required;
}
void load_dva(uint32_t& micro_missiles, float missile_power_required){
    micro_missiles = std::ceil(missile_power_required / 60);
}
float matrix_power(uint32_t* bots_power, size_t bots_number, float boss_power){
    float total_damage = 0;
    for(auto i = 0; i < bots_number; i++)
        total_damage += bots_power[i];
    total_damage += boss_power;
    return total_damage;
}




//reports the combat data 
class combat_report{
    public:
        combat_report(size_t bots, float boss_power, uint32_t micro_missiles, float defense_matrix_power)
         : bots(bots), boss_power(boss_power), micro_missiles(micro_missiles), defense_matrix_power(defense_matrix_power)
        {
        }
        //streamline report to any output stream 
        friend std::ostream& operator << (std::ostream& os, combat_report& report){
            os << "D.Va's Combat Report\n"
            << "Combat with " << report.bots << " enemy bots and one enemy boss with power " << report.boss_power << ".\n"
            << "Loaded mech with 10 micro missiles and the defense matrix with power " << report.defense_matrix_power << ".\n"
            << "Ready for combat!";

            return os;
        }
    private:
        size_t bots;
        float boss_power;
        uint32_t micro_missiles;
        float defense_matrix_power;
};

// stores parsed data from combat file 
class combat_details{
    public:
        combat_details(){

        }
        ~combat_details(){
            delete[] botsPower;
        }
        // load combat info from any input stream
        friend std::istream& operator >> (std::istream& is, combat_details& details){
            is >> details.botsCount;
            if (details.bossPower) //check if this is only a boss fight
                details.botsPower = new uint32_t[details.botsCount];
            for (auto i = 0; i < details.botsCount; i++)
                is >> details.botsPower[i];
            is >> details.bossPower >> details.microMissiles >> details.defenseMatrix;
            return is;
        }
        combat_report create_report(){
            float matrixPowerRequired = matrix_power(botsPower, botsCount, bossPower);
            float missilePowerRequired = 0;

            for (auto i = 0; i < botsCount; i++)
                missilePowerRequired += single_missile_power(botsPower[i]);
                missilePowerRequired += single_missile_power(bossPower);

            load_dva(matrixPowerRequired, defenseMatrix);
            load_dva(microMissiles, missilePowerRequired);

            return combat_report(botsCount, bossPower, microMissiles, defenseMatrix);
        }
    private:
        size_t botsCount;
        uint32_t* botsPower = NULL;
        float bossPower;
        uint32_t microMissiles;
        float defenseMatrix;
};


int main(int argc, char** argv){
    char* input_file_path="combat.txt", *output_file_path="report.txt";
    if (argc == 3) //if user wants to supply custom path 
    {
        input_file_path = argv[1];
        output_file_path = argv[2];
    }
     

    combat_details details; 
    std::ifstream in_stream(input_file_path);
    if (!in_stream.is_open()) return EXIT_FAILURE;    
    in_stream >> details;
    in_stream.close();

    auto report = details.create_report();
    std::ofstream out_stream(output_file_path);
    if (!out_stream.is_open()) return EXIT_FAILURE;
    out_stream << report;
    out_stream.close();
 
    return EXIT_SUCCESS;
}