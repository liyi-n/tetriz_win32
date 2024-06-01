#include "game.h"
#include "tetromino.h"
#include "utils.h"
//#include "define.h"
namespace gm
{
    //---------------------定义变量区-----------
    bool running;
    bool holding;
    bool ending;
    Piece one_piece;
    Matrix playfield;
    bool reseting;
    std::chrono::microseconds duration;
    Matrix frame;
    bool locking;
    bool helping;
    std::queue<Tetromino> next;
    Tetromino hold_piece;
    int score,level,lines;
    //-----------------------------------------------------
    // int row,col;
    // Tetromino_1 cur;
    // Tetromino_2 cur_set;
    // Tetromino cur_s;
    // int cur_index;
    void init()
    {
        srand(std::time(0));//让随机数的种子变化
        locking=false;
        running=true;
        holding=false;
        ending = false;
        reseting=false;
        helping=false;
        score = lines =0;
        //level =1;
        levelup();
        //playfield[y][x],x=0-9 y=0-21       --------------|----------->x
        playfield = Matrix(22,std::vector<int>(10,0));
        //load();//是否加载初始地图
        preview();
        one_piece = pick();
        
        //row=2;
        //col=15;
        //cur=O;
        //cur_set = I_set;
        //cur_index =0;
        //cur_s = i;
        //duration = 500ms;
        frame = playfield;
        
    }
    void process()
    {
        if(ending)
            return;
        render();
        if(ut::timer(duration))
        {
            //如果无法继续下落，锁定在游戏区域
            if(one_piece.down())
                return;
            if(locking)
            {

            //锁定
            lock();
          
            //消行
            clear();
            levelup();
            one_piece=pick();
            locking=false;
            holding=false;
            reseting=false;
            }
            else
            {
                locking=true;
            }
        }
    }
    void render()
    {
        /* auto [x,y]=one_piece.get_xy();
        //正常块
        //[0,4)
        for(auto i:iota(0,4))
        {
            auto [dx,dy]=one_piece.get_mino(i);
            frame[y+dy][x+dx]=one_piece.get_color();
        }
        //阴影块
        while(one_piece.test(x,--y));
        y++;
        for(auto i:iota(0,4))
        {
            auto [dx,dy]=one_piece.get_mino(i);
            if(frame[y+dy][x+dx]==0)
                frame[y+dy][x+dx]=0-one_piece.get_color();
        }*/
        frame=playfield;
        //正常块
        merge(frame,one_piece);
        //阴影块
        Piece ghost = one_piece;
        ghost.set_ghost();
        while (ghost.down())
            ;
        merge(frame,ghost);
       
        
    }
    Piece pick()
    {
        //todo:拿5格预览队列里面的第一个元素
        //static std::vector<Tetromino> bag={i,j,l,o,s,t,z};
        assert(next.size()>0);
        Piece p(next.front(),4,20,0);
        next.pop();
        if(!p.test(4,20))
        {
            //game over!
            ending = true;
        }
        preview();
        //p.set_playfield(std::make_shared<Matrix>(playfield));

        return std::move(p);
    }

    void lock()
    {
        /*auto [x,y]=one_piece.get_xy();
        for(auto i : iota(0,4))
        {
            auto [dx,dy]=one_piece.get_mino(i);
            playfield[y+dy][x+dx]=one_piece.get_color();
        }*/
        merge(playfield,one_piece);//用merge函数简化了操作
    }

    void clear()
    {
        int count = 0;
        for(auto it =playfield.begin();it != playfield.end();)
        {
            bool full =true;
            for(auto cell:*it)
            {
                if(cell==0)
                {
                    full=false;
                    break;
                }
            }
            if(full)
            {
                //消行[1,2,3,4]-->[1,3,4]
                it = playfield.erase(it);
                playfield.push_back(std::vector<int>(it->size(),0));
                count++;
            }
            else
            {
                ++it;
            }
        }
        if(count==1) score+=100*level;
        if(count==2) score+=300*level;
        if(count==3) score+=500*level;
        if(count==4) score+=800*level;
        lines+=count;
    }

    void quit()
    {
        running=false;
    }
    void rotate(int i)
    {
       // cur = rotate(cur);
       //cur_index=(cur_index+1)%4;
       one_piece.rotate(i);
    }
    void left()
    {   
        //col--;
        one_piece.left();
    }
    void right()
    {
        //col++;
        one_piece.right();
    }
    void down()
    {
        //row++;
        if(one_piece.down())
            score+=1;
    }

    void drop()
    {
        while(one_piece.down())
            score+=2;
        locking=true;
    }
    void preview()
    {
        static std::vector<Tetromino> bag={i,j,l,o,s,t,z};
        int index;
        while (next.size()<5)
        {
            index = rand() % bag.size();
            next.push(bag[index]);
            bag.erase(bag.begin()+index);
            if(bag.size()==0)
                bag={i,j,l,o,s,t,z};
        }
        
    }
    void load()
    {
        std::ifstream fs("tetriz.map");
        assert(fs.is_open());
        std::string line;
        // 22*10
        for(auto &row:playfield | std::ranges::views::take(20) | std::ranges::views::reverse)
        {
            getline(fs,line);
            for (auto i :iota(0,10))
            {
                if (line[i]=='1')
                {
                    row[i]=(int)Color::Gray;
                }
            }
        }
        fs.close();
    }

    //1.如果暂存区为空，当前块存入暂存区，重新生成一个当前块
    //2.如果暂存区非空，当前块存入暂存区，使用原暂存区的块重新生成一个当前块，从头下落
    //3.每一个回合只能使用一次暂存
    void hold()
    {
        if(holding)
            return;
        if(hold_piece.empty())
        {
            hold_piece = one_piece.get_tetromino();
            one_piece = pick();
        }
        else
        {
            auto tmp=hold_piece;
            hold_piece = one_piece.get_tetromino();
            one_piece = Piece(tmp,4,20,0);
        }
        holding=true;
    }
    void levelup()
    {
        //每消除10行 升级
        level = lines/10+1;
        duration;
        //Time = (0.8-((level-1)*0.007))^(level-1)
        duration = std::chrono::milliseconds(int(pow((0.8 - ((level - 1) * 0.007)), level - 1) * 1000));
    }
    void reset()
    {
        init();
        reseting=true;
    }
    void help()
    {
        helping=!helping;
        reseting=!helping;//当helping显示 不做reset
    }
    void merge(Matrix &m, const Piece &p)
    {
        auto[x,y] = p.get_xy();
        for(auto i :iota(0,4))
        {
            auto [dx,dy]=p.get_mino(i);
            if(m[y+dy][x+dx]==0)
                m[y+dy][x+dx] = p.get_color();
        }
    }
}
