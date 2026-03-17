#include <cstring>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <memory>
#include <type_traits>

template <typename TTag>
struct dispatch;

template <>
struct dispatch<struct ptr_interconvertible_tag>
{
    struct object1
    {
        int a;
        int b;
        int c;
    };

    struct object2
    {
        int a;
        char c;
    };

    static void apply()
    {
        object1 obj1{1, 2, 3};
        object1* ptr1 = &obj1;

        int* ptr2 = reinterpret_cast<int*>(&obj1);
        std::cout << *ptr2 << std::endl;
        ++ptr2;
        std::cout << *ptr2 << std::endl;
        ++ptr2;
        std::cout << *ptr2 << std::endl;
    }
};

template <>
struct dispatch<struct lifetime_tag>
{
    struct point
    {
        int x;
        int y;
    };
    static void apply()
    {
        alignas(point) unsigned char bytes[sizeof(point)];

        point p{1024, 4096};

        std::memcpy(bytes, &p, sizeof(point));

        //        point* ptr = std::start_lifetime_as<point>(bytes); // need gcc 16
    }
};

template <>
struct dispatch<struct pointer_cmp_tag>
{
    static void apply()
    {
        int a{33};
        int b{44};

        if (reinterpret_cast<uintptr_t>(&a) < reinterpret_cast<uintptr_t>(&b))
        {
            std::cout << "a is less than b in terms of memory address" << std::endl;
        }
    }
};

template<>
struct dispatch<struct bitcast_tag> {

};

int main(int argc, char** argv)
{
    dispatch<struct pointer_cmp_tag>::apply();
    return 0;
}
