#include <cassert>
#include <compare>

namespace legacy {
class MagicInt
{
public:
    constexpr MagicInt(int v)
        : v_{v}
    {}
    constexpr MagicInt(MagicInt const&) = default;
    constexpr MagicInt& operator=(MagicInt const&) = default;
    constexpr MagicInt(MagicInt&&) noexcept = default;
    constexpr MagicInt& operator=(MagicInt&&) noexcept = default;
    constexpr int value() const { return v_; }
    constexpr friend bool operator==(MagicInt const& lhs, MagicInt const& rhs) { return lhs.v_ == rhs.v_; }
    constexpr friend bool operator!=(MagicInt const& lhs, MagicInt const& rhs) { return !(lhs == rhs); }
    constexpr friend bool operator<(MagicInt const& lhs, MagicInt const& rhs) { return lhs.v_ < rhs.v_; }
    constexpr friend bool operator<=(MagicInt const& lhs, MagicInt const& rhs) { return lhs.v_ <= rhs.v_; }
    constexpr friend bool operator>(MagicInt const& lhs, MagicInt const& rhs) { return lhs.v_ > rhs.v_; }
    constexpr friend bool operator>=(MagicInt const& lhs, MagicInt const& rhs) { return lhs.v_ >= rhs.v_; }
    ~MagicInt() = default;
private:
    int v_{};
};

namespace test {

consteval void test()
{
    static constexpr MagicInt a(3);
    static constexpr MagicInt b(3);

    static_assert(a == b);
    static_assert(a <= b);

    static constexpr MagicInt c(3);
    static constexpr MagicInt d(4);

    static_assert(c != d);
    static_assert(c <= d);
}

} // namespace test

} // namespace legacy

namespace cpp20 {

class MagicInt
{
public:
    constexpr MagicInt(int v)
        : v_{v}
    {}
    constexpr MagicInt(MagicInt const&) = default;
    constexpr MagicInt& operator=(MagicInt const&) = default;
    constexpr MagicInt(MagicInt&&) noexcept = default;
    constexpr MagicInt& operator=(MagicInt&&) noexcept = default;
    constexpr int value() const { return v_; }

    constexpr bool operator==(MagicInt const& rhs) const { return v_ == rhs.v_; }
    constexpr bool operator!=(MagicInt const& rhs) const { return v_ != rhs.v_; }
    constexpr bool operator<(MagicInt const& rhs) const { return v_ < rhs.v_; }
    constexpr bool operator<=(MagicInt const& rhs) const { return v_ <= rhs.v_; }
    constexpr bool operator>(MagicInt const& rhs) const { return v_ > rhs.v_; }
    constexpr bool operator>=(MagicInt const& rhs) const { return v_ >= rhs.v_; }

    ~MagicInt() = default;
private:
    int v_{};
};

namespace test {

constexpr void test()
{
    static constexpr MagicInt a(3);
    static constexpr MagicInt b(3);

    static_assert(a == b);
    static_assert(a <= b);

    static constexpr MagicInt c(3);
    static constexpr MagicInt d(4);

    static_assert(c != d);
    static_assert(c <= d);
}

} // namespace test

} // namespace cpp20

namespace spaceship {

class MagicInt
{
public:
    constexpr MagicInt(int v)
        : v_{v}
    {}
    constexpr MagicInt(MagicInt const&) = default;
    constexpr MagicInt& operator=(MagicInt const&) = default;
    constexpr MagicInt(MagicInt&&) noexcept = default;
    constexpr MagicInt& operator=(MagicInt&&) noexcept = default;
    constexpr int value() const { return v_; }
    constexpr auto operator<=>(MagicInt const& rhs) const = default;
    ~MagicInt() = default;
private:
    int v_{};
};

namespace test {

consteval void test()
{
    static constexpr MagicInt a(3);
    static constexpr MagicInt b(3);

    static_assert(a == b);
    static_assert(a <= b);

    static constexpr MagicInt c(3);
    static constexpr MagicInt d(4);

    static_assert(c != d);
    static_assert(c <= d);
}

} // namespace test

} // namespace spaceship

int main(int argc, char** argv)
{
    legacy::test::test();
    cpp20::test::test();
    spaceship::test::test();

    return 0;
}
