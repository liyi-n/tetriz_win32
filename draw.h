#pragma once

#include "define.h"
#include "tetromino.h"
/*
ui:layout
dw:draw
tc:terminal control
gm:game logic
ut:utils
*/
namespace dw
{
    void window(int top,int left,int width,int height,std::string title);
    void frame(Matrix& frame,int top,int left);
    void next(std::queue<Tetromino> next5,int top,int left);
    void hold(Tetromino &h,int top,int left);
    //-----------------------------------------
    void matrix(Matrix& m,int top,int left,Matrix* buffer=nullptr,std::string blank="  ");
}