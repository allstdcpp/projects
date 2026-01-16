#include <cmath>
#include <expected>
#include <iostream>
#include <string>

template <typename TTag>
struct dispatch;

template <>
struct dispatch<struct division_tag>
{
    static void apply()
    {
        auto f = [](double n, double d) -> std::expected<double, std::string> {
            if (d == 0.0)
            {
                return std::unexpected("Error: Division by zero");
            }
            return n / d;
        };

        auto a = f(6, 3);

        if (a.has_value())
        {
            std::cout << "1. the value of 6 / 3: " << a.value() << std::endl;
        }

        if (a)
        {
            std::cout << "2. the value of 6 / 3: " << *a << std::endl;
        }

        auto b = f(2, 0);

        if (!b)
        {
            std::cout << "3. the value of 2 / 0; " << b.error() << std::endl;
        }
    }
};

template <>
struct dispatch<struct map_tag>
{
    static void apply()
    {
        auto fs = [](double n, double d) -> std::expected<double, std::string> {
            if (n == 0)
            {
                return std::unexpected(std::string{"Divide by zero"});
            }
            return std::expected<double, std::string>(n / d);
        };

        std::cout << "fmap: " << fs(12, 2).transform([](double v) { return v / 2; }).value_or(0) << std::endl;
    }
};

template <>
struct dispatch<struct chaining_unsafe_ops>
{
    static void apply()
    {
        auto divide = [](double n, double d) -> std::expected<double, std::string> {
            if (n == 0)
            {
                return std::unexpected(std::string{"Divide by zero"});
            }
            return std::expected<double, std::string>(n / d);
        };

        auto sqrt = [](double n) -> std::expected<double, std::string> {
            if (n <= 0)
            {
                return std::unexpected(std::string{"sqrt less than equal to zero"});
            }
            return std::expected<double, std::string>(std::sqrt(n));
        };

        std::cout << "bind: " << divide(100, 4).and_then(sqrt).value_or(0) << std::endl;
    }
};
int main(int argc, char** argv)
{
    dispatch<struct chaining_unsafe_ops>::apply();
    return 0;
}
