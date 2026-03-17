#include <cassert>
#include <iostream>
#include <memory>
#include <memory_resource>
#include <utility>

namespace ds {

template <typename T, typename Allocator>
class dynamic_optional_impl
{
public:
    using allocator_type = Allocator;
    using traits = std::allocator_traits<allocator_type>;
    using value_type = typename traits::value_type;
    using pointer = typename traits::pointer;
    using const_pointer = typename traits::const_pointer;
    using size_type = typename traits::size_type;
    using difference_type = typename traits::difference_type;

    dynamic_optional_impl(allocator_type allocator)
        : allocator_{allocator}
    {}

    dynamic_optional_impl(dynamic_optional_impl&& rhs) noexcept
        : allocator_{rhs.allocator_}
        , ptr_{std::exchange(rhs.ptr_, nullptr)}
        , constructed_{std::exchange(rhs.constructed_, false)}
    {}

    dynamic_optional_impl(dynamic_optional_impl&& rhs, allocator_type& alloc) noexcept
        : allocator_{alloc}
    {
        if (!rhs.constructed_)
            return;

        if (rhs.allocator_ == alloc)
        {
            ptr_ = std::exchange(rhs.ptr_, nullptr);
            constructed_ = std::exchange(rhs.constructed_, false);
        }
        else
        {
            create(std::move_if_noexcept(*rhs.ptr_));
            rhs.destroy();
        }
    }

    void allocate() { ptr_ = traits::allocate(allocator_, 1); }

    template <typename... Us>
    void construct(Us&&... args)
    {
        assert(ptr_);
        traits::construct(allocator_, ptr_, std::forward<Us>(args)...);
        constructed_ = true;
    }

    template <typename... Us>
    void create(Us&&... args)
    {
        ptr_ = traits::allocate(allocator_, 1);
        traits::construct(allocator_, ptr_, std::forward<Us>(args)...);
        constructed_ = true;
    }

    void destroy() noexcept
    requires std::is_trivially_destructible_v<T>
    {
        if (ptr_)
            traits::deallocate(allocator_, ptr_, 1);
        ptr_ = nullptr;
        constructed_ = false;
    }

    void destroy() noexcept
    {
        if (constructed_)
            traits::destroy(allocator_, ptr_);

        if (ptr_)
            traits::deallocate(allocator_, ptr_, 1);

        constructed_ = false;
        ptr_ = nullptr;
    }

    ~dynamic_optional_impl()
    requires std::is_trivially_destructible_v<T>
    {
        if (ptr_)
            traits::deallocate(allocator_, ptr_, 1);
    }

    void swap(dynamic_optional_impl& rhs) noexcept
    {
        if constexpr (traits::propagate_on_container_swap::value)
        {
            std::swap(rhs.ptr_, ptr_);
            std::swap(rhs.constructed_, constructed_);
            std::swap(rhs.allocator_, allocator_);
            return;
        }

        if (rhs.allocator_ == allocator_ || traits::is_always_equal::value)
        {
            std::swap(rhs.ptr_, ptr_);
            std::swap(rhs.constructed_, constructed_);
        }
        else
        {
            std::unreachable();
        }
    }

    ~dynamic_optional_impl()
    {
        if (constructed_)
            traits::destroy(allocator_, ptr_);

        if (ptr_)
            traits::deallocate(allocator_, ptr_, 1);
    }

    [[no_unique_address]] allocator_type allocator_;
    pointer ptr_{};
    bool constructed_{};
};

template <typename T, typename Allocator = std::allocator<T>>
class dynamic_optional : private dynamic_optional_impl<T, Allocator>
{
public:
    using base = dynamic_optional_impl<T, Allocator>;
    using allocator_type = typename base::allocator_type;
    using traits = typename base::traits;
    using value_type = typename base::value_type;
    using pointer = typename base::pointer;
    using const_pointer = typename base::const_pointer;
    using size_type = typename base::size_type;
    using difference_type = typename base::difference_type;
    using reference = value_type&;
    using const_reference = value_type const&;

    dynamic_optional(allocator_type allocator = allocator_type())
        : base(allocator)
    {}

    template <typename... Us>
    dynamic_optional(std::allocator_arg_t arg, allocator_type allocator, Us&&... args)
        : base(allocator)
    {
        base::create(std::forward<Us>(args)...);
    }

    dynamic_optional(dynamic_optional const& rhs)
        : base(traits::select_on_container_copy_construction(rhs.allocator_))
    {
        if (rhs.empty())
            return;

        assert(rhs.constructed_);

        base::create(*rhs.ptr_);
    }

    dynamic_optional(dynamic_optional const& rhs, allocator_type& alloc)
        : base(alloc)
    {
        if (rhs.empty())
            return;

        assert(rhs.constructed_);
        base::create(*rhs.ptr_);
    }

    using base::swap;

    template <typename... Us>
    reference emplace(Us&&... args)
    {
        dynamic_optional tmp{this->allocator_};
        tmp.create(std::forward<Us>(args)...);

        swap(tmp);

        return *this->get();
    }

    dynamic_optional(dynamic_optional&& rhs) noexcept
        : base(std::move(rhs))
    {}

    dynamic_optional(dynamic_optional&& rhs, allocator_type& alloc) noexcept
        : base(std::move(rhs), alloc)
    {}

    dynamic_optional& operator=(dynamic_optional const& rhs)
    {
        static constexpr auto pocca = traits::propagate_on_container_copy_assignment::value;

        dynamic_optional tmp{pocca ? rhs.allocator_ : this->allocator_};

        if (rhs)
        {
            tmp.create(*rhs.ptr_);
        }

        if constexpr (pocca)
        {
            this->destroy();
            this->allocator_ = rhs.allocator_;
        }

        swap(tmp);

        return *this;
    }

    dynamic_optional& operator=(dynamic_optional&& rhs)
    {
        static constexpr auto pocma = traits::propagate_on_container_move_assignment::value;

        dynamic_optional tmp{pocma ? rhs.allocator_ : this->allocator_};

        if constexpr (pocma)
        {
            this->destroy();

            tmp.ptr_ = std::exchange(rhs.ptr_, nullptr);
            tmp.constructed_ = std::exchange(rhs.constructed_, false);
            this->allocator_ = rhs.allocator_;
        }
        else
        {
            if (this->allocator_ == rhs.allocator_)
            {
                tmp.ptr_ = std::exchange(rhs.ptr_, nullptr);
                tmp.constructed_ = std::exchange(rhs.constructed_, false);
            }
            else if (rhs)
            {
                tmp.create(std::move_if_noexcept(*rhs.ptr_));
                this->destroy();
            }
        }

        swap(tmp);

        return *this;
    }

    friend void swap(dynamic_optional& lhs, dynamic_optional& rhs) noexcept { lhs.swap(rhs); }

    reference operator*() { return *this->ptr_; }
    const_reference operator*() const { return *this->ptr_; }
    pointer operator->() { return this->ptr_; }
    const_pointer operator->() const { return this->ptr_; }
    pointer get() { return this->ptr_; }
    const_pointer get() const { return this->ptr_; }
    operator bool() const { return this->constructed_; }
    bool empty() const { return !this->constructed_; }

    ~dynamic_optional() = default;
};

} // namespace ds

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

int main(int argc, char** argv)
{
    using namespace ds;

    alignas(point) std::byte buffer[120];
    std::pmr::monotonic_buffer_resource resource{&buffer, sizeof(buffer)};
    std::pmr::polymorphic_allocator<point> alloc{&resource};

    dynamic_optional<point, std::pmr::polymorphic_allocator<point>> d1{std::allocator_arg, alloc, 4, 5};

    d1.emplace(3, 2);

    auto d2 = d1;
    auto d4 = d1;

    decltype(d1) d3{d1, alloc};
    d3.emplace(8, 9);

    d3 = std::move(d1);

    return 0;
}
