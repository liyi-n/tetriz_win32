#pragma once
#include <iostream>
#include <chrono>
#include <string>
#include <thread>
//#include <termio.h>
#include <map>
#include <functional>
#include <vector>
#include <memory>
#include <cassert>
#include <ranges>
#include <sstream>
#include <ostream>
#include <queue>
#include <fstream>
#include <cmath>

#ifdef __linux__
#include <termios.h>
#elif _WIN32
#include <conio.h>
#elif __APPLE__
#endif
using namespace std::chrono_literals;
/*此文件可以避免后续新建文件反复写#include XXX*/
#define KEY_Q 'q'
#define KEY_W 'w'
#define KEY_S 's'
#define KEY_A 'a'
#define KEY_D 'd'
#define KEY_Z 'z'//左旋
#define KEY_X 'x'
#define KEY_C 'c'//暂存
#define KEY_R 'r'//游戏重开
#define KEY_H 'h'//游戏帮助
#define KEY_SPACE ' '
using Matrix=std::vector<std::vector<int>>;//定义矩阵
using Tetromino = std::vector<std::vector<std::pair<int,int>>>;
using Offset = std::vector<std::vector<std::pair<int,int>>>;
using std::ranges::views::iota;