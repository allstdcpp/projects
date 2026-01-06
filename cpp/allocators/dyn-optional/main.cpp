#include <memory>
#include <utility>

namespace ds {
template <typename T, typename Allocator = std::allocator<T>>
class dyn_optional_impl
{
public:
    using allocator_type = Allocator;
    struct construct_tag
    {};

    dyn_optional_impl(allocator_type allocator)
        : allocator_{allocator}
    {}

    dyn_optional_impl(allocator_type allocator, T* ptr)
        : allocator_{allocator}
        , ptr_{ptr}
    {}

    dyn_optional_impl(allocator_type allocator, [[maybe_unused]] construct_tag _)
        : allocator_{allocator}
        , ptr_{std::allocator_traits<Allocator>::allocate(allocator_, sizeof(T))}
    {}

    dyn_optional_impl(dyn_optional_impl const&) = delete;
    dyn_optional_impl& operator=(dyn_optional_impl const&) = delete;
    ~dyn_optional_impl()
    {
        if (ptr_)
            std::allocator_traits<Allocator>::deallocate(allocator_, ptr_, sizeof(T));
    }

protected:
    [[no_unique_address]] allocator_type allocator_;
    T* ptr_{};
};

template <typename T, typename Allocator = std::allocator<T>>
class dyn_optional : dyn_optional_impl<T, Allocator>
{
public:
    using base_type = dyn_optional_impl<T, Allocator>;
    using allocator_type = dyn_optional_impl<T, Allocator>::allocator_type;

    dyn_optional(allocator_type allocator = allocator_type())
        : dyn_optional_impl<T, Allocator>(allocator)
    {}

    dyn_optional(T const& v, allocator_type allocator = allocator_type())
        : dyn_optional_impl<T, Allocator>(allocator, typename base_type::construct_tag{})
    {
        std::allocator_traits<Allocator>::construct(this->allocator_, this->ptr_, v);
    }

    dyn_optional(T&& v, allocator_type allocator = allocator_type())
        : dyn_optional_impl<T, Allocator>(allocator, typename base_type::construct_tag{})
    {
        std::allocator_traits<Allocator>::construct(this->allocator_, this->ptr_, std::move(v));
    }

    dyn_optional(dyn_optional const& rhs)
        : dyn_optional_impl<T, Allocator>(
              std::allocator_traits<Allocator>::select_on_container_copy_construction(rhs.allocator_))
    {
        if (rhs.has_value())
        {
            this->ptr_ = std::allocator_traits<Allocator>::allocate(this->allocator_, sizeof(T));
            std::allocator_traits<Allocator>::construct(this->allocator_, this->ptr_, *this->ptr_);
        }
    }

    dyn_optional(dyn_optional const& rhs, allocator_type allocator)
        : dyn_optional_impl<T, Allocator>(allocator)
    {
        if (rhs.has_value())
        {
            this->ptr_ = std::allocator_traits<Allocator>::allocate(this->allocator_, sizeof(T));
            std::allocator_traits<Allocator>::construct(this->allocator_, this->ptr_, *this->ptr_);
        }
    }

    dyn_optional& operator=(dyn_optional const& rhs)
    {
        if (this != &rhs)
        {}
        return *this;
    }

    dyn_optional(dyn_optional&& rhs)
        : dyn_optional_impl<T, Allocator>(rhs.allocator_, std::exchange(rhs.ptr_, nullptr))
    {}

    dyn_optional(dyn_optional&& rhs, allocator_type const& allocator)
        : dyn_optional_impl<T, Allocator>(allocator, std::exchange(rhs.ptr_, nullptr))
    {}

    T const& value() const { return *this->ptr_; }
    T& value() { return *this->ptr_; }
    bool has_value() const { return this->ptr_ != nullptr; }

    ~dyn_optional()
    {
        if (this->ptr_)
            std::allocator_traits<Allocator>::destroy(this->allocator_, this->ptr_);
    }
};

} // namespace ds

int main(int argc, char** argv)
{
    using namespace ds;

    dyn_optional<int> d1{42};
    auto d2 = d1;
    auto d3 = std::move(d2);

    return 0;
}
