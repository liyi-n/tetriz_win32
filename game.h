#pragma once
#include "tetromino.h"
#include "piece.h"
namespace gm
{
    //==================================================
    //游戏变量定义
    //==================================================
    //游戏运行状态
    extern bool running;
    //锁定标志
    extern bool locking;
    //暂存标志
    extern bool holding;
    //终结标志
    extern bool ending;
    //帮助标志
    extern bool helping;
    //当前掉落的块
    extern Piece one_piece;
    //重置标志
    extern bool reseting;
    //游戏场地
    
    extern Matrix playfield;
    //每帧时间间隔
    extern std::chrono::microseconds duration;
    //当前渲染帧
    extern Matrix frame;
    //五格预览
    extern std::queue<Tetromino> next;
    //暂存块
    extern Tetromino hold_piece;
    //==================================================
    //游戏逻辑
    //==================================================
    //游戏主逻辑
    void process();
    //游戏初始化
    extern int col,row;
    void init();
    //渲染帧
    void render();
    //获取一个块
    Piece pick();
    //锁定
    void lock();
    //消行
    void clear();
    //退出
    void quit();
    //键盘操作
    
    void rotate(int i);
    void left();
    void right();
    void down();
    //直落
    void drop();
    //生成预览队列
    void preview();
    //载入预设地图
    void load();
    //暂存
    void hold();
    //积分 等级 消行
    extern int score,level,lines;
    //省级
    void levelup();
    //游戏重开
    void reset();
    //游戏帮助
    void help();
    //------------------------------
    void merge(Matrix& m,const Piece& p);
    //extern Tetromino_1 cur;
    //extern Tetromino_2 cur_set;
    //extern Tetromino cur_s;
    //extern int cur_index;
}
/*
Single 100xlevel 100xlevel
Double 300xlevel 300xlevel
Triple 500xlevel 500xlevel
Tetris 800xlevel 800xlevel
Soft drop 1 point  per cell 1 point per cell
Hard drop 2 points per cell 2 point cell
*/