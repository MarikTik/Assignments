#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <ostream>
#include <cstddef>

// I wrote the classes required for the extra credit.
// the requirements for load() function are beyond my understanding.
// I used the previous implementation of my code with some changes 

// Sorry but the rules for this assignment are too vague and restrictive at the same time 
// it is harder to get down to what the expectation is than to think of the implementation.
// why not give us requirement file and solution file and let us implement everything however we want 
// (restricting to oop of course)?

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
    if (micro_missiles > 10)
        micro_missiles = std::ceil(missile_power_required / 60);
}
float matrix_power(uint32_t* bots_power, size_t bots_number, float boss_power){
    float power = 0;
    for (auto i = 0; i < bots_number; i++) power += bots_power[i];
    return power + boss_power;
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
            is >> details.bossPower;
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
        uint32_t microMissiles = 10;
        float defenseMatrix = 100.0;
};
 

 
#include <cmath>

class Battle{
    public:
    
        Battle(float boss_power, size_t bots_count, uint32_t* bots_power) 
            : bossPower(boss_power), botsCount(bots_count), botsPower(bots_power)
        {
        }
       
        float matrix_power(){
            float power = 0;
            for (auto i = 0; i < botsCount; i++) power += botsPower[i];
            return power + bossPower;
        }
private:
    friend class Mech;
    size_t botsCount; 
    float bossPower;
    uint32_t* botsPower;

     
};

class Mech{
    public:
        float micro_missile(Battle& battle){
            float total = 0;
            for (auto i = 0; i < battle.botsCount; i++)
                total += 2 * battle.botsPower[i];
            return total + 5 * battle.bossPower;
        }
        void load(float matrixPowerRequired, float missilePowerRequired){
            if (missilePowerRequired > microMissiles)
                microMissiles = std::ceil(missilePowerRequired / 60);
            if (defenseMatrix < matrixPowerRequired)
                defenseMatrix = matrixPowerRequired;
        }
        float get_defense_matrix() const{
            return defenseMatrix;
        }
        uint32_t get_micro_missiles() const{
            return microMissiles;
        }
    private:
        float defenseMatrix = 100.0;
        uint32_t microMissiles = 10;
};


 
int main(int argc, char** argv){
    const char* input_file_path="combat.txt", *output_file_path="report.txt";
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