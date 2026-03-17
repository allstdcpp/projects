#include <filesystem>
#include <fstream>
#include <iostream>

template <typename TTag>
struct dispatch;

template <>
struct dispatch<struct lsb_tag>
{
    static void apply()
    {
        int a = 0b00000110;
        auto lsb = (a & (-a));

        std::cout << "initial value: " << a << ", lsb value is: " << lsb << std::endl;
    }
};

template <>
struct dispatch<struct poweroftwo_tag>
{
    static void apply()
    {
        int v = 32;

        auto b = (v > 0) && ((v & (v - 1)) == 0);

        std::cout << std::boolalpha << "Is power of 2: " << b << std::endl;
    }
};

template <>
struct dispatch<struct clear_lsb_tag>
{
    static void apply()
    {
        int a = 0b00000110;
        int b = (a & (a - 1));

        std::cout << "initial value: " << a << ", lsb bit dropped is: " << b << std::endl;
    }
};

int main(int argc, char** argv)
{
    dispatch<struct clear_lsb_tag>::apply();
    return 0;
}
