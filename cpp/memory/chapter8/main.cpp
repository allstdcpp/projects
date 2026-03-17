#include <cstdlib>
#include <iostream>

int aligned_allocs{};
int allocs{};

void* operator new(std::size_t count)
{
    auto ptr = std::malloc(count);

    if (!ptr)
        throw std::bad_alloc{};

    ++allocs;
    return ptr;
}
void* operator new[](std::size_t count)
{
    auto ptr = std::malloc(count);

    if (!ptr)
        throw std::bad_alloc{};

    ++allocs;
    return ptr;
}
void* operator new(std::size_t count, std::align_val_t align)
{
    auto ptr = std::aligned_alloc(static_cast<std::size_t>(align), count);

    if (!ptr)
        throw std::bad_alloc{};

    ++aligned_allocs;
    return ptr;
}
void* operator new[](std::size_t count, std::align_val_t align)
{
    auto ptr = std::aligned_alloc(static_cast<std::size_t>(align), count);

    if (!ptr)
        throw std::bad_alloc{};

    ++aligned_allocs;
    return ptr;
}

void* operator new(std::size_t count, [[maybe_unused]] const std::nothrow_t& tag) noexcept
{
    auto ptr = std::malloc(count);
    if (ptr)
        ++allocs;
    return ptr;
}

void* operator new[](std::size_t count, [[maybe_unused]] const std::nothrow_t& tag) noexcept
{
    auto ptr = std::malloc(count);
    if (ptr)
        ++allocs;
    return ptr;
}

int main() { return 0; }
