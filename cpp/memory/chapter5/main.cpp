#include <iostream>
#include <memory>

template <typename TTag>
struct dispatch;

template <>
struct dispatch<struct unique_ptr_tag>
{
    static void apply()
    {
        std::unique_ptr<int> p{new int{42}};

        if (p)
        {
            std::cout << "Value: " << *p << std::endl;
            std::cout << "Value: " << *(p.get()) << std::endl;
            p.reset(new int(52));

            std::cout << "Value2: " << *p << std::endl;
            auto q = p.release();
            std::cout << "Value2: " << *q << std::endl;

            delete q;
        }
    }
};

template <>
struct dispatch<struct unique_ptr_array_tag>
{
    static void apply()
    {
        auto size = 3;
        std::unique_ptr<int[]> p{new int[size]{0}};

        for (auto i = 0; i < size; ++i)
        {
            p[i] = i;
        }
        for (auto i = 0; i < size; ++i)
        {
            std::cout << p[i] << std::endl;
        }
    }
};

template <>
struct dispatch<struct unique_ptr_custom_deleter>
{
    template <typename T>
    struct deleter
    {
        void operator()(T const* p)
        {
            std::cout << "deleting: " << *p << std::endl;
            delete p;
        }
    };

    static void apply() { std::unique_ptr<int, deleter<int>> p{new int{42}}; }
};

int main()
{
    dispatch<struct unique_ptr_custom_deleter>::apply();

    return 0;
}
