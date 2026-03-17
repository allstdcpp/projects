#include <array>
#include <cassert>
#include <concepts>
#include <cstdint>
#include <iostream>
#include <list>
#include <map>
#include <unordered_map>

namespace finance {

enum class side : std::uint8_t
{
    buy = 0,
    sell = 1
};

template <size_t N, size_t M>
concept char_array_in_bounds = requires(char (&a)[N]) { requires M < N; };

template <size_t N>
class fixed_string
{
public:
    using value_type = char;
    using pointer = value_type*;
    using const_pointer = const value_type*;
    using reference = value_type&;
    using const_reference = const value_type&;
    using iterator = value_type*;
    using const_iterator = const value_type*;
    using size_type = size_t;

    fixed_string() = default;

    template <size_t M>
    fixed_string(char (&a)[M])
    requires char_array_in_bounds<N, M>
        : data_{&a, &a + M}
        , size_{M}
    {
        data_[size_] = '\0';
    }
    fixed_string(const_pointer str, size_type length)
        : data_{str, str + length}
        , size_{length}
    {
        assert(length <= N);
        data_[size_] = '\0';
    }

    fixed_string(fixed_string const&) = default;
    fixed_string& operator=(fixed_string const&) = default;
    fixed_string(fixed_string&&) = default;
    fixed_string& operator=(fixed_string&&) = default;
    reference operator[](size_type index) { return data_[index]; }
    const_reference operator[](size_type index) const { return data_[index]; }
    reference front() { return data_[0]; }
    const_reference front() const { return data_[0]; }
    reference back() { return data_[size_ - 1]; }
    const_reference back() const { return data_[size_ - 1]; }
    iterator begin() { return &data_[0]; }
    iterator end() { return &data_[0] + size_; }
    const_iterator begin() const { return &data_[0]; }
    const_iterator end() const { return &data_[0] + size_; }
    const_iterator cbegin() { return &data_[0]; }
    const_iterator cend() { return &data_[0] + size_; }
    const_iterator cbegin() const { return &data_[0]; }
    const_iterator cend() const { return &data_[0] + size_; }
    size_type size() const noexcept { return size_; }
    bool empty() const noexcept { return size_ == 0; }
    auto operator<=>(fixed_string const& rhs) const = default;
    size_type hash() const { return 13; }
    ~fixed_string() = default;
private:
    std::array<char, N + 1> data_{0};
    size_type size_{0};
};

class price_depth
{};

class order_book
{
public:
    using symbol = fixed_string<5>;
using bids = std::map < double,

      private:
};

class exchange
{
public:
    using symbol = fixed_string<5>;
    using order_books = std::unordered_map<symbol, order_book>;


private:
};

} // namespace finance

namespace std {
template <>
struct std::hash<finance::fixed_string<5>>
{
    size_t operator()(finance::fixed_string<5> const& rhs) { return rhs.hash(); }
};
} // namespace std
int main(int argc, char** argv) { return 0; }
