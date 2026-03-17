#include <filesystem>
#include <fstream>
#include <iostream>
#include <type_traits>

template <typename TTag>
struct dispatch;

template <>
struct dispatch<struct object_repr_tag>
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

    static constexpr void apply()
    {
        static_assert(std::has_unique_object_representations_v<object1>);
        static_assert(!std::has_unique_object_representations_v<object2>);
    }
};

int main(int argc, char** argv)
{
    dispatch<struct object_repr_tag>::apply();
    return 0;
}
