#include <iostream>
#include <memory_resource>
#include <ostream>
#include <string>
#include <string_view>
#include <vector>

namespace allocators {

class memory_statistics_resource : public std::pmr::memory_resource
{
public:
    memory_statistics_resource(std::string_view name, std::pmr::memory_resource* upstream)
        : name_{name}
        , upstream_{upstream}
    {}

private:
    void* do_allocate(size_t __bytes, size_t __alignment)
    {
        auto alloc = upstream_->allocate(__bytes, __alignment);

        ++total_allocations_;
        ++current_allocations_;

        total_allocated_space_ += __bytes;
        current_allocated_space_ += __bytes;

        return alloc;
    }

    void do_deallocate(void* __p, size_t __bytes, size_t __alignment)
    {
        upstream_->deallocate(__p, __bytes, __alignment);

        --current_allocations_;
        current_allocated_space_ -= __bytes;
    }

    friend std::ostream& operator<<(std::ostream& o, memory_statistics_resource const& r)
    {
        o << "Statistics for Allocations\n";
        o << "Total Allocations: " << r.total_allocations_ << "\n";
        o << "Still Active Allocations: " << r.current_allocations_ << "\n";
        o << "Total Allocated Bytes: " << r.total_allocated_space_ << "\n";
        o << "Still Active Allocated Bytes: " << r.current_allocated_space_ << "\n";
        return o;
    }

    bool do_is_equal(const memory_resource& __other) const noexcept { return &__other == upstream_; }

    std::string_view name_;
    std::pmr::memory_resource* upstream_;

    std::size_t total_allocations_{};
    std::size_t current_allocations_{};
    std::size_t total_allocated_space_{};
    std::size_t current_allocated_space_{};
};

} // namespace allocators

void example1(bool run = false)
{
    if (!run)
        return;

    std::byte buffer[4096];

    std::pmr::monotonic_buffer_resource resource{&buffer, sizeof(buffer), std::pmr::null_memory_resource()};
    allocators::memory_statistics_resource stats{"stats", &resource};

    {
        std::pmr::polymorphic_allocator<> alloc{&stats};
        std::pmr::vector<std::pmr::string> v{alloc};

        for (auto i = 0; i < 10; ++i)
        {
            auto const* message = "This is a super large string that should exceed the small string optimisation";
            v.emplace_back(message);
        }
    }

    std::cout << stats << std::endl;
}

class person
{
public:
    using allocator_type = std::pmr::polymorphic_allocator<>;

    person(std::pmr::string first, std::pmr::string last, allocator_type alloc = allocator_type())
        : first_{std::move(first), alloc}
        , last_{std::move(last), alloc}
    {}

    person(person const& rhs, allocator_type alloc = allocator_type())
        : first_{rhs.first_, alloc}
        , last_{rhs.last_, alloc}
    {}

    person(person&& rhs) = default;
    person(person&& rhs, allocator_type& alloc)
        : first_{std::move(rhs.first_), alloc}
    {}

    person& operator=(person const& rhs) = default;
    person& operator=(person&& rhs) = default;

    ~person() = default;
private:
    std::pmr::string first_;
    std::pmr::string last_;
};

int main(int argc, char** argv)
{
    example1(true);
    return 0;
}
