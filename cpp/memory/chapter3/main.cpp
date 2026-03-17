#include <iostream>

template <typename TTag>
struct dispatch;

template <>
struct dispatch<struct static_cast_tag>
{
    static void apply()
    {
        float a{3.14f};
        int b = static_cast<int>(a);

        std::cout << b << std::endl;
    }
};

int main() { return 0; }
