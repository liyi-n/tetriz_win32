#include <iostream>
#include "terminal.h"
#include <thread>//能够识别时间单位
#include <chrono>
#include "utils.h"
#include "draw.h"
using namespace std::chrono_literals;
#include "define.h"
#include "control.h"
#include "game.h"
#include "tetromino.h"
#include "window.h"


//1.init中只采用一次性绘制
//2.只绘制屏幕变化的部分，不变化不更新
//3.减少stdout的次数      寄存器-->cache-->memory-->io device
void init()
{
#ifdef _WIN32
    system("chcp 65001");//让powershell使用UTF-8编码
#endif
    
    tc::hide_cursor();
    tc::clean_screen();
    ui::show_windows();
    ui::show_help();
    gm::init();
    gm::start_listener();
}

void loop()
{
    int i=1;
    while(gm::running)
    {
        gm::process();
        ui::show_info();
        ui::show_game();
        

       // tc::move_to(gm::row,ut::block2col(gm::col));//方块超过20行重新显示
        //tc::set_back_color(15);
        //std::cout<<"  ";
       
        //dw::tetromino(gm::cur_s,gm::row,gm::col,gm::cur_index);
        
        
        std::this_thread::sleep_for(8ms);//fps = 1000/100=10
        tc::reset_color();
    }

}

void exit()
{
    tc::show_cursor();
    ui::show_exit();
    tc::reset_color();
}

int main()
{
    //std::cout<<"\033[5;10H" << "\033[38;5;214m]"<<"Hello world"<<"\033[10;1H]";//直接使用ANSI控制代码

    /*tc::move_to(5,10);
    tc::set_forth_color(214);
    cout<<"Hello world!";
    tc::move_to(10,1);
    此段程序实现了较为简单的光标移动效果*/
    init();
    loop();
    exit();
    
    
    return 0;
}
