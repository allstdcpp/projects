#include <cassert>
#include <iostream>
#include <utility>

namespace allocators {

template <typename T, size_t Align>
struct freelist_node
{};

class freelist_storage
{
public:
    unsigned char* start_{};
    unsigned char* aligned_start_{};
    size_t size_{};
};

template <size_t N>
consteval auto is_power_of_2() -> bool
{
    return N > 0 && (N & (N - 1)) == 0;
}

template <size_t N>
concept power_of_2 = requires() { requires(is_power_of_2<N>()); };

template <typename T, size_t Align = alignof(T)>
requires power_of_2<Align>
class freelist_allocator
{
public:
    using value_type = T;

    freelist_allocator() noexcept = default;
    explicit freelist_allocator(freelist_storage& storage)
        : storage_{&storage}
    {}
    freelist_allocator(freelist_allocator const&) noexcept = default;
    freelist_allocator& operator=(freelist_allocator const&) noexcept = default;
    freelist_allocator(freelist_allocator&&) noexcept = default;
    freelist_allocator& operator=(freelist_allocator&&) noexcept = default;
    ~freelist_allocator() = default;
private:
    freelist_storage* storage_{};
};

} // namespace allocators

struct point
{
    point() = default;
    point(int a, int b)
        : x{a}
        , y{b}
    {}
    int x;
    int y;
};

int main(int argc, char** argv) { return 0; }
