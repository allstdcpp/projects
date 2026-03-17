#include <concepts>
#include <cstring>
#include <iostream>
#include <memory>
#include <type_traits>

namespace restl {

template <typename T>
class vector_impl
{
public:
    vector_impl() = default;
    vector_impl(size_t capacity)
        : data_{(capacity > 0) ? static_cast<T*>(::operator new[](capacity * sizeof(T))) : static_cast<T*>(nullptr)}
        , capacity_{capacity}
    {}
    vector_impl(vector_impl const&) = delete;
    vector_impl& operator=(vector_impl const&) = delete;
    vector_impl(vector_impl&&) = delete;
    vector_impl& operator=(vector_impl&&) = delete;

    ~vector_impl()
    requires std::is_trivially_destructible_v<T>
    {
        ::operator delete[](data_);
    }

    ~vector_impl()
    {
        for (decltype(size_) i = 0; i < size_; ++i)
            std::destroy_at(data_ + i);
        ::operator delete[](data_);
    }

    T* data_{};
    size_t size_{};
    size_t capacity_{};
};

template <typename T>
class vector : private vector_impl<T>
{
public:
    vector() = default;
    vector(size_t n)
        : vector_impl<T>(n)
    {}

    vector(vector const& rhs)
        : vector_impl<T>(rhs.size_)
    {
        if constexpr (std::is_trivially_copyable_v<T>)
        {
            std::memcpy(this->data_, rhs.data_, rhs.size_ * sizeof(T));
            this->size_ = rhs.size_;
        }
        else
        {
            for (decltype(this->size_) i = 0; i < this->size_; ++i)
            {
                std::construct_at(this->data_ + i, rhs.data_[i]);
                ++this->size_;
            }
        }
    }

    vector& operator=(vector const& rhs)
    {
        (vector<T>{rhs}).swap(*this);
        return *this;
    }

    vector(vector&& rhs) noexcept
    {
        std::swap(this->data_, rhs.data_);
        std::swap(this->size_, rhs.size_);
        std::swap(this->capacity_, rhs.capacity_);
    }

    vector& operator=(vector&& rhs) noexcept
    {
        vector<T>(std::move(rhs)).swap(*this);
        return *this;
    }

    void swap(vector<T>& rhs)
    {
        using std::swap;
        std::swap(this->data_, rhs.data_);
        std::swap(this->size_, rhs.size_);
        std::swap(this->capacity_, rhs.capacity_);
    }

    void push_back(T const& v)
    {
        if (this->size_ == this->capacity_)
        {
            vector<T> n{this->capacity_ * 2 + 1};
            for (decltype(this->size_) i = 0; i < this->size_; ++i)
            {
                n.push_back(this->data_[i]);
            }
            n.swap(*this);
            this->push_back(v);
        }
        else
        {
            std::construct_at(this->data_ + this->size_, v);
            ++this->size_;
        }
    }

    T const& operator[](size_t index) const { return this->data_[index]; }
    T& operator[](size_t index) { return this->data_[index]; }
    size_t size() const { return this->size_; }
    bool empty() const { return this->size_ == 0; }

    ~vector() = default;
};

} // namespace restl
//
struct point
{
    int x;
    int y;

    friend std::ostream& operator<<(std::ostream& o, point const& p)
    {
        o << p.x << ", " << p.y;
        return o;
    }
};

int main()
{
    restl::vector<point> v1{3};
    v1.push_back(point{1, 2});
    v1.push_back(point{2, 2});
    v1.push_back(point{3, 2});
    v1.push_back(point{4, 2});

    auto v2 = v1;

    for (size_t i = 0; i < v1.size(); ++i)
        std::cout << v2[i] << std::endl;

    return 0;
}
