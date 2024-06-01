#pragma once

namespace gm
{
    extern char command;
    //char getch();//WIN系统下采用其本身函数


    void key_event();//键盘监听函数
    void start_listener();
    //键盘操作函数
    void command_quit();
    void command_rotate_R();
    void command_rotate_L();
    void command_rotate_2();
    void command_left();
    void command_right();
    void command_down();
    void command_drop();
    void command_hold();
    void command_reset();
    void command_help();
 
}