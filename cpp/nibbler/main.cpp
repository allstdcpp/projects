#include <concepts>
#include <iostream>

namespace nibbler {

template <size_t S, size_t N>
struct bit_range
{
    constexpr bit_range() = default;
    constexpr bit_range(bit_range const&) = default;
    constexpr bit_range& operator=(bit_range const&) = default;
    constexpr ~bit_range() = default;
};

template <size_t S, size_t N>
consteval auto bit_range_for() -> bit_range<S, N>
{
    return {};
}

template <typename T, size_t S, size_t N>
requires std::integral<T>
constexpr auto operator&(bit_range<S, N> _) -> T
{}

} // namespace nibbler

int main(int argc, char** argv) { return 0; }
