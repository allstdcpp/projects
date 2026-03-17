#include <concepts>
#include <cstring>
#include <iostream>
#include <memory>
#include <type_traits>

struct point
{
    int x;
    int y;
};

void malloc_example()
{
    point* ptr = static_cast<point*>(std::malloc(3 * sizeof(point)));

    for (auto i = 0; i < 3; ++i)
    {
        ptr[i].x = i;
        ptr[i].y = i;
    }
    for (auto i = 0; i < 3; ++i)
    {
        std::cout << ptr[i].x << ", " << ptr[i].y << std::endl;
    }

    std::free(ptr);
}

int main()
{
    malloc_example();
    return 0;
}
