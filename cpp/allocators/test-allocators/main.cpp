#include <iostream>
#include <memory_resource>
#include <ostream>
#include <string>
#include <string_view>
#include <vector>

namespace allocators {

class test_resource : public std::pmr::memory_resource
{
public:
    test_resource(std::string_view name, std::pmr::memory_resource* upstream)
        : name_{name}
        , upstream_(upstream)
    {}

private:
    void* do_allocate(std::size_t bytes, std::size_t alignment) override
    {
        std::cout << "Allocating " << bytes << " bytes with an alignment of " << alignment << std::endl;
        return upstream_->allocate(bytes, alignment);
    }

    void do_deallocate(void* p, std::size_t bytes, std::size_t alignment) override
    {
        std::cout << "Deallocating " << bytes << " bytes with an alignment of " << alignment << " at address "
                  << std::hex << p << std::endl;
        upstream_->deallocate(p, bytes, alignment);
    }

    bool do_is_equal(std::pmr::memory_resource const& other) const noexcept override { return upstream_ == &other; }

    std::string_view name_;
    std::pmr::memory_resource* upstream_;
};

} // namespace allocators
//
class person
{
public:
    using allocator_type = std::pmr::polymorphic_allocator<std::byte>;

    person() = default;
    person(std::pmr::string first, std::pmr::string last, allocator_type alloc = allocator_type())
        : first_{std::move(first), alloc}
        , last_{std::move(last), alloc}
    {}
    person(person const&) = default;
    person(person const& rhs, allocator_type alloc)
        : first_{rhs.first_, alloc}
        , last_{rhs.last_, alloc}
    {}
    person& operator=(person const&) = default;
    person(person&&) = default;
    person(person&& rhs, allocator_type alloc)
        : first_{std::move(rhs.first_), alloc}
        , last_{std::move(rhs.last_), alloc}
    {}
    person& operator=(person&&) = default;
    std::pmr::string const& first() const { return first_; }
    std::pmr::string const& last() const { return last_; }
    ~person() = default;
private:
    std::pmr::string first_;
    std::pmr::string last_;
};

int main(int argc, char** argv)
{
    allocators::test_resource resource{"test_resource", std::pmr::get_default_resource()};
    std::pmr::polymorphic_allocator<std::byte> allocator{&resource};
    std::pmr::vector<person> vs{allocator};

    vs.emplace_back("Blair", "Davidson");
    vs.emplace_back("Alice", "Davidson");

    return 0;
}
