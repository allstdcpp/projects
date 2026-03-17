#include <iostream>

template <typename TTag>
struct dispatch;

namespace memory {
template <typename T>
class shared_ptr
{
public:

    class control_block
    {};


private:
    T* ptr_{};
    control_block* cptr_{};
};

} // namespace memory

int main() { return 0; }
