#include <filesystem>
#include <fstream>
#include <iostream>

template <typename TTag>
struct dispatch;

template <>
struct dispatch<struct path_tag>
{
    static void apply()
    {
        std::filesystem::path tmp{"/tmp"};
        std::cout << std::boolalpha << "path: " << tmp.string() << ", exists: " << std::filesystem::exists(tmp)
                  << std::endl;
    }
};

template <>
struct dispatch<struct create_dirs>
{
    static void apply()
    {
        std::filesystem::path tmp{"/tmp/a/b/c"};

        std::error_code ec;

        if (std::filesystem::create_directories(tmp))
        {
            std::cout << "created directory: " << tmp.string() << std::endl;
        }
    }
};

template <>
struct dispatch<struct path_info_tag>
{
    static void apply()
    {
        std::filesystem::path tmp{"/tmp/a/b/c"};

        std::error_code ec;

        if (std::filesystem::create_directories(tmp))
        {
            std::cout << "created directory: " << tmp.string() << std::endl;
        }

        auto file = tmp / "test.txt";

        {
            std::fstream fs{file.c_str()};
            fs << "Hello world....";
        }

        std::cout << "path: " << std::endl;

        {
            std::filesystem::remove_all(file);
        }
    }
};

int main(int argc, char** argv)
{
    dispatch<struct create_dirs>::apply();
    return 0;
}
