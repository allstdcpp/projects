#include <cstdint>
#include <iostream>

std::string hex(int8_t v) {
    static constexpr const char values[] = "0123456789abcdef";
    std::string result(2, ' ');

    uint8_t val = v;
    result[0] = values[val >> 4]; 
    result[1] = values[val & 15]; 

    return result;
}

int main()
{
    std::cout << hex(32) << std::endl;
}
