#include "utils.h"
#include <chrono>
#include <locale>//转换编码格式1
#include <codecvt>//转换格式
#include "define.h"
using namespace std::chrono_literals;
namespace ut
{
    int fps()
    {
        

        static auto start = std::chrono::steady_clock::now();//C++20后的时间计量函数
        //auto end = start;
        static int frame_count = 0;
        static int fps=0;
        auto end =std::chrono::steady_clock::now();//end因为在多个类都有含义，可能出现定义不清晰
        frame_count++;
        if(end-start>1s)
        {
            fps = frame_count;
            frame_count = 0;
            start= end;
        }

        return fps;
    }

    std::string utf32_to_utf8(std::u32string str)
    {
        std::wstring_convert<std::codecvt_utf8<char32_t>,char32_t> convert;
        return convert.to_bytes(str);
    }

    bool timer(std::chrono::microseconds sec)
    {
        static auto start = std::chrono::steady_clock::now();
        auto end = std::chrono::steady_clock::now();
        if (end - start > sec)
        {
            start=end;
            return true;
        }
        return false;
    }

}

