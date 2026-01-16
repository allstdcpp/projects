#include <tuple>
#include <type_traits>

namespace meta {

template <typename... Ts>
struct list
{};

namespace detail {

template <typename L1, typename L2>
struct assign;

template <template <typename...> typename L1, template <typename...> typename L2, typename... Ts, typename... Us>
struct assign<L1<Ts...>, L2<Us...>> : std::type_identity<L1<Us...>>
{};

template <typename L>
struct rest;

template <template <typename...> typename L, typename T, typename... Ts>
struct rest<L<T, Ts...>> : std::type_identity<L<Ts...>>
{};

template <template <typename> typename F, typename L>
struct transform;

template <template <typename> typename F, template <typename...> typename L, typename... Ts>
struct transform<F, L<Ts...>> : std::type_identity<L<F<Ts>...>>
{};

template <template <typename...> typename F, typename L>
struct apply;

template <template <typename...> typename F, template <typename...> typename L, typename... Ts>
struct apply<F, L<Ts...>> : std::type_identity<F<Ts...>>
{};

template <template <typename...> typename Dest, typename L>
struct explode;

template <template <typename...> typename Dest, template <typename...> typename L, typename... Ts>
struct explode<Dest, L<Ts...>> : apply<Dest, L<Ts...>>
{};

template <typename... Ts>
struct size : std::type_identity<std::integral_constant<int, sizeof...(Ts)>>
{};

template <template <typename...> typename T, typename... Ts>
struct size<T<Ts...>> : std::type_identity<std::integral_constant<int, sizeof...(Ts)>>
{};

template <typename T, typename L>
struct push_front;

template <typename T, template <typename...> typename L, typename... Ts>
struct push_front<T, L<Ts...>> : std::type_identity<L<T, Ts...>>
{};

template <typename T, typename L>
struct push_back;

template <typename T, template <typename...> typename L, typename... Ts>
struct push_back<T, L<Ts...>> : std::type_identity<L<Ts..., T>>
{};

template <typename... Ts>
struct front;

template <typename T, typename... Ts>
struct front<T, Ts...> : std::type_identity<T>
{};

template <template <typename...> typename L, typename T, typename... Ts>
struct front<L<T, Ts...>> : std::type_identity<T>
{};

template <typename... Ts>
struct back;

template <typename T>
struct back<T> : std::type_identity<T>
{};

template <typename T, typename... Ts>
struct back<T, Ts...> : back<Ts...>
{};

template <template <typename...> typename L, typename T>
struct back<L<T>> : std::type_identity<T>
{};

template <template <typename...> typename L, typename... Ts, typename T>
struct back<L<T, Ts...>> : back<L<Ts...>>
{};

template <typename L1, typename L2>
struct append;

template <template <typename...> typename L1, template <typename...> typename L2, typename... Ts, typename... Us>
struct append<L1<Ts...>, L2<Us...>> : std::type_identity<L1<Ts..., Us...>>
{};

template <typename T, typename L>
struct count;

template <typename T, template <typename...> typename L>
struct count<T, L<>> : std::type_identity<std::integral_constant<int, 0>>
{};

template <typename T, typename U, template <typename...> typename L, typename... Ts>
struct count<T, L<U, Ts...>> : count<T, L<Ts...>>
{};

template <typename T, template <typename...> typename L, typename... Ts>
struct count<T, L<T, Ts...>> : std::type_identity<std::integral_constant<int, count<T, L<Ts...>>::type::value + 1>>
{};

} // namespace detail

template <typename L1, typename L2>
using assign = typename detail::assign<L1, L2>::type;

template <typename L1>
using clear = assign<L1, list<>>;

template <template <typename...> typename F, typename L1>
using apply = typename detail::apply<F, L1>::type;

template <template <typename...> typename Dest, typename L1>
using explode = typename detail::apply<Dest, L1>::type;

template <typename T>
using size = detail::size<T>;

template <typename... Ts>
using front = typename detail::front<Ts...>::type;

template <typename... Ts>
using back = typename detail::back<Ts...>::type;

template <template <typename> typename F, typename L>
using transform = typename detail::transform<F, L>::type;

template <typename L>
using rest = typename detail::rest<L>::type;

template <typename L>
using empty = std::bool_constant<(size<L>::type::value == 0)>;

template <typename L>
using non_empty = std::bool_constant<(size<L>::type::value > 0)>;

template <typename T>
using pop_front = detail::rest<T>;

template <typename T, typename L>
using push_front = typename detail::push_front<T, L>::type;

template <typename T, typename L>
using push_back = typename detail::push_back<T, L>::type;

template <typename L1, typename L2>
using append = typename detail::append<L1, L2>::type;

template <typename T, typename L>
using count = typename detail::count<T, L>::type;

namespace tests {

consteval void size_empty_tuple() { static_assert(size<std::tuple<>>::type::value == 0); }

consteval void size_non_empty_tuple() { static_assert(size<std::tuple<int, int>>::type::value == 2); }

consteval void front_non_empty_tuple() { static_assert(std::is_same_v<int, front<std::tuple<int, double>>>); }

consteval void front_non_empty_pack() { static_assert(std::is_same_v<int, front<int, double, long>>); }

consteval void back_single_element_tuple() { static_assert(std::is_same_v<int, back<std::tuple<int>>>); }

consteval void back_multiple_element_tuple() { static_assert(std::is_same_v<int, back<std::tuple<double, int>>>); }

consteval void back_non_empty_single_pack() { static_assert(std::is_same_v<long, back<long>>); }

consteval void back_non_empty_multiple_pack() { static_assert(std::is_same_v<long, back<int, double, long>>); }

consteval void transform_non_empty_multiple_tuple()
{
    using list = std::tuple<int, double, float>;
    using expected = std::tuple<const int, const double, const float>;
    static_assert(std::is_same_v<expected, meta::transform<std::add_const_t, list>>);
}

consteval void transform_non_empty_single_tuple()
{
    using list = std::tuple<int>;
    using expected = std::tuple<const int>;
    static_assert(std::is_same_v<expected, meta::transform<std::add_const_t, list>>);
}

consteval void apply_function_test_with_multiple_args()
{
    using list = std::tuple<int, int>;
    static_assert(meta::apply<std::is_same, list>::value);
}

consteval void explode_function_test_with_multiple_args()
{
    using list = std::tuple<int, int>;
    static_assert(std::is_same_v<meta::explode<meta::list, list>, meta::list<int, int>>);
}

consteval void empty_function_test_with_non_empty_list()
{
    static_assert(empty<std::tuple<int, int>>::type::value == false);
}

consteval void empty_function_test_with_empty_list() { static_assert(empty<std::tuple<>>::type::value == true); }

consteval void push_front_non_empty_multiple_tuple()
{
    using list = std::tuple<int, int>;
    static_assert(std::is_same_v<meta::push_front<double, list>, std::tuple<double, int, int>>);
}

consteval void push_back_non_empty_multiple_tuple()
{
    using list = std::tuple<int, int>;
    static_assert(std::is_same_v<meta::push_back<double, list>, std::tuple<int, int, double>>);
}

consteval void append_multiple_non_empty_tuples()
{
    using l1 = std::tuple<int, long>;
    using l2 = std::tuple<float, double>;
    static_assert(std::is_same_v<meta::append<l1, l2>, std::tuple<int, long, float, double>>);
}

consteval void count_non_empty_multiple_tuple()
{
    using list = std::tuple<int, int>;
    static_assert(meta::count<int, list>::type::value == 2);
}

consteval void count_empty_uple()
{
    using list = std::tuple<>;
    static_assert(meta::count<int, list>::type::value == 0);
}
} // namespace tests

} // namespace meta

int main(int argc, char** argv) { return 0; }
