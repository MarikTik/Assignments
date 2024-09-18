#include <iostream>

std::string run_length_encode(const std::string &str){
    if (str.size() == 1)
        return str;
    if (str.size() == 2)
        return str + "1";

    size_t count = 1;
    std::string compressed_str;
   
    for(size_t i = 0; i < str.size(); i++){
        if (str[i] != str[i + 1]){
            compressed_str += str[i];
            compressed_str += std::to_string(count);
            count = 1;
        }
        else count ++;
    }
    return compressed_str;
}

int main(){
    std::string str;
    std::cin >> str;
    std::string encoded_string = run_length_encode(str);
    std::cout << "\nencoded string: " << encoded_string;
    std::cout << "\ncompression rate: " << encoded_string.size() / double(str.size()) << std::endl;
}