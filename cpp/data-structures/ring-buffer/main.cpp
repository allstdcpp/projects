#include <algorithm>
#include <array>
#include <cassert>
#include <iostream>
#include <utility>

#include <boost/optional.hpp>

namespace ds {
template <typename T, size_t N>
class ring_buffer
{
public:
    using value_type = T;
    using size_type = size_t;
    using reference = T&;
    using const_reference = T const&;
    using pointer = T*;
    using const_pointer = T const*;
    using storage_type = std::array<value_type, N>;

    constexpr ring_buffer() = default;
    constexpr ring_buffer(ring_buffer const&) = default;
    constexpr ring_buffer& operator=(ring_buffer const&) = default;
    constexpr ring_buffer(ring_buffer&&) noexcept = default;
    constexpr ring_buffer& operator=(ring_buffer&&) noexcept = default;

    template <typename U>
    void push_back(U&& value)
    {
        storage_[tail_] = std::forward<U>(value);
        ++count_;
        if (tail_ == head_)
        {
            head_ = (head_ + 1) % N;
        }
        tail_ = (tail_ + 1) % N;
    }

    reference front() { return storage_[head_]; }
    const_reference front() const { return storage_[head_]; }
    reference back() { return storage_[(tail_ == 0) ? N - 1 : tail_ - 1]; }
    const_reference back() const { return storage_[(tail_ == 0) ? N - 1 : tail_ - 1]; }
    size_type size() const { return std::clamp(count_, static_cast<size_t>(0), N); }
    bool empty() const { return count_ == 0; }

    constexpr ~ring_buffer() = default;
private:
    storage_type storage_;
    size_type tail_{0}; // write index - back of the queue
    size_type head_{}; // read index - front of the queue
    size_type count_{};
};

} // namespace ds

int main(int argc, char** argv)
{
    ds::ring_buffer<int, 2> q;
    std::cout << "size: " << q.size() << std::endl;
    std::cout << "empty: " << q.empty() << std::endl;
    q.push_back(1);
    std::cout << "empty: " << q.empty() << std::endl;
    q.push_back(2);

    std::cout << "front: " << q.front() << std::endl;
    std::cout << "back: " << q.back() << std::endl;
    std::cout << "size: " << q.size() << std::endl;
    std::cout << "empty: " << q.empty() << std::endl;
    q.push_back(3);
    std::cout << "size: " << q.size() << std::endl;
    std::cout << "empty: " << q.empty() << std::endl;
    std::cout << "front: " << q.front() << std::endl;
    std::cout << "back: " << q.back() << std::endl;
    return 0;
}
