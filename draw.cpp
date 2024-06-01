#include "draw.h"
#include "terminal.h"
#include <iostream>
#include "utils.h"
#include <vector>
#include "piece.h"
#include "game.h"
/*
 	0	1	2	3	4	5	6	7	8	9	A	乙	C	D	乙	F
U+250x	──	──	│	┃	┄	┅	┆	┇	┈	┉	┊	┋	┌	┍	┎	┏
U+251x	┐	┑	┒	┓	└	┕	┖	┗	┘	┙	┚	┛	├	┝	┞	┟
U+252x	┠	┡	┢	┣	┤	┥	┦	┧	┨	┩	┪	┫	┬	┭	┮	┯
U+253x	┰	┱	┲	┳	┴	┵	┶	┷	┸	┹	┺	┻	┼	┽	┾	┿
U+254x	╀	╁	╂	╃	╄	╅	╆	╇	╈	╉	╊	╋	╌	╍	╎	╏
U+255x	═	║	╒	╓	╔	╕	╖	╗	╘	╙	╚	╛	╜	╝	╞	╟
U+256x	╠	╡	╢	╣	╤	╥	╦	╧	╨	╩	╪	╫	╬	╭	╮	╯
U+257x	╰	╱	╲	╳	╴	╵	╶	╷	╸	╹	╺	╻	╼	╽	╾	╿
*/
/*
 ┌────────────┐
 │


*/
namespace dw
{   //此处如果直接定义字符集，由于字符有20位置
    const std::u32string style1 = U" ┌┐└┘│─";
    const std::u32string style2 = U" ┏┓┗┛┃╍";
    const std::u32string style3 = U" ╔╗╚╝║═";
    const std::u32string cur_style = style3;//调整该项实现边框的不同风格

    void window(int top, int left, int width, int height,std::string title)
    {   

        for(int r=0;r<height;++r){
            tc::move_to(top+r,ut::block2col(left));
            for(int c=0;c<width;++c)
            {
                if(r==0)//第一行
                {
                    if(c==0)//第一列
                    {
                        //std::cout<<" ┌";
                        std::cout<<ut::utf32_to_utf8({cur_style[0],cur_style[1]});
                    }
                    else if(c==width-1)//最后一列
                    {
                        //std::cout<<"┐";
                        std::cout<<ut::utf32_to_utf8({cur_style[2]});;
                    }
                    else
                    {
                        //std::cout<<"──";//两个-
                        std::cout<<ut::utf32_to_utf8({cur_style[6],cur_style[6]});
                    }
                }
                else if(r==height-1)//最后一行
                {
                     if(c==0)//第一列
                    {
                        //std::cout<<" └";
                        std::cout<<ut::utf32_to_utf8({cur_style[0],cur_style[3]});
                    }
                    else if(c==width-1)//最后一列
                    {
                        //std::cout<<"┘";
                        std::cout<<ut::utf32_to_utf8({cur_style[4]});
                    }
                    else
                    {
                        //std::cout<<"──";
                        std::cout<<ut::utf32_to_utf8({cur_style[6],cur_style[6]});
                    }
                }
                else
                {
                     if(c==0)//第一列
                    {
                        //std::cout<<" │";
                        std::cout<<ut::utf32_to_utf8({cur_style[0],cur_style[5]});
                    }
                    else if(c==width-1)//最后一列
                    {
                        //std::cout<<"│";
                        std::cout<<ut::utf32_to_utf8({cur_style[5]});
                    }
                    else
                    {
                        std::cout<<"  ";
                    }
                }
            }
            
        }
        //title
            tc::move_to(top,ut::block2col(left)+(width*2-title.length())/2);
            std::cout<<title;
    }
    
    void frame(Matrix &frame, int top, int left)
    {
        /*static Matrix buffer(frame.size(),std::vector<int>(frame[0].size(),-1));
        Matrix f(frame.begin(),frame.begin()+20);
        matrix(f,top,left,&buffer,"\u30FB");
        std::ostringstream oss;*/
        //frame xy---> row/col
        int row,col;
        static Matrix buffer(frame.size(),std::vector<int>(frame[0].size(),-1));
        if (gm::reseting)
        {
            buffer = Matrix(frame.size(),std::vector<int>(frame[0].size(),-1));
        }
        for(int x=0;x<10;++x)
        {
            for(int y=0;y<20;++y)
            {
                if (buffer[y][x]==frame[y][x]) continue;//如果方块没变化，就不更新了
                buffer[y][x]=frame[y][x];
                
                row = top+20-y-1;
                col = left+x;
                tc::move_to(row,ut::block2col(col));
                if(frame[y][x]>0)//正常块
                {
                    tc::reset_color();
                    tc::set_back_color(frame[y][x]);
                    std::cout<<"  ";
                }
                else if(frame[y][x]<0)//阴影块
                {
                    tc::reset_color();
                    tc::set_forth_color(0-frame[y][x]);
                    std::cout<<"\u25e3\u25e5";
                }
                else //空白
                {
                    tc::reset_color();
                    std::cout<<"\u30FB";
                }
            }
        }
    }
    void next(std::queue<Tetromino> next5, int top, int left)
    {
        static Matrix buffer(15,std::vector<int>(6,-1));
        Matrix next_field(15,std::vector<int>(6,0));
        for (int y=12;next5.size()>0;y -= 3)
        {
            gm::Piece p(next5.front(),2,y,0);//给中心点坐标
            gm::merge(next_field,p);
            next5.pop();
        }
        matrix(next_field,top,left,&buffer);
    }
    void hold(Tetromino &h, int top, int left)
    {
        static Matrix buffer(4,std::vector<int>(7,-1));
        Matrix hold_field(4,std::vector<int>(7,0));
        if(!h.empty())
        {
        gm::Piece p(h,3,1,0);
        if(gm::holding)
        {
            p.set_disable();
        }
        gm::merge(hold_field,p);
        matrix(hold_field,top,left,&buffer);

        }
        
    }
    void matrix(Matrix &m, int top, int left, Matrix *buffer, std::string blank)
    {
        // frame xy--------> row/col
        //std::ostringstream oss;
         int row,col;
        //static Matrix buffer(m.size(),std::vector<int>(m[0].size(),-1));
        for(int y=0;y<m.size();++y)
        {
            for(int x=0;x<m[0].size();++x)
            {
                if(buffer !=nullptr)
                {
                    if ((*buffer)[y][x]==m[y][x]) 
                        continue;//如果方块没变化，就不更新了
                    (*buffer)[y][x]=m[y][x];
                }
                
                
                row = top+m.size()-y-1;
                col = left+x;
                tc::move_to(row,ut::block2col(col));
                if(m[y][x]>0)//正常块
                {
                    tc::reset_color();
                    tc::set_back_color(m[y][x]);
                    std::cout<<"  ";//这个东西非常重要
                }
                else if(m[y][x]<0)//阴影块
                {
                    tc::reset_color();
                    tc::set_forth_color(0-m[y][x]);
                    std::cout<<"\u25e3\u25e5";
                }
                else //空白
                {
                    tc::reset_color();
                    std::cout<<blank;//"\u30FB"
                }
            }
        }
    }
}
    