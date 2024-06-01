#pragma once
#include <string>
#include <chrono>
namespace ut
{
    int fps();
    std::string utf32_to_utf8(std::u32string str);
    
    inline int block2col(int b)
    {
        return 2 * b - 1;
    }
    bool timer(std::chrono::microseconds sec);
} // namespace