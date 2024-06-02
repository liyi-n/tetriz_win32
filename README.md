# 俄罗斯方块小游戏
* 一个基于C++语言的俄罗斯方块游戏，采用CMake进行编译。程序编写在Ubuntu系统下进行，此为程序编写后进行兼容性调整的版本
  ![0001-0557-ezgif com-video-to-gif-converter](https://github.com/liyi-n/tetriz_win32/assets/153268142/b12fe6cd-466b-4985-8dc2-461a5f1ce5b9)

-----------------------------
## 游戏界面
![Snipaste_2024-06-01_21-07-19](https://github.com/liyi-n/tetriz_win32/assets/153268142/35e0fced-8c8f-4cc0-bbc2-67061670bc6a)
* 游戏共分为五个区域，其中：
* Hold：查看暂存方块。暂存每个方块下落只能用一次，使用后暂存区方块为白色。
* Status：此区域显示当前游戏等级/得分/已消除行数。每消除十行等级加一，方块下落速度增加。
具体得分计算可参考：https://harddrop.com/wiki/Tetris_Worlds
* Tetriz：显示俄罗斯方块游戏主界面。
* Next：显示后面五个方块预览。
* Info：帮助提示，按H可以呼出指南。
## 编译指南
1. 确保已经安装CMake(版本号为3.22及以上)
2. 克隆和下载此仓库到本地
3. 本程序采用Visual Studio Community 2019 Release-x86编译
4. 程序已经过兼容性修正，可在win10中运行
## 运行指南
1. 可在设置好的编译环境中，运行源代码开始游戏
2. 也可直接在Windows Powershell运行tetriz_32.exe文件(已打包为压缩包)
## 游戏玩法
* A/S/D：控制方块左/下/右移
* W/Z/X：控制方块右旋/左旋/对旋
* 空格：方块直落
* C：方块暂存
* H：游戏帮助，呼出键盘指示
* R；游戏重启
* Q：游戏退出
### 说明
本项目为C++代码练习，旨在熟悉语法和编译过程。  
structure.xlsx文档旨在方便查询方块位置，可以利用该表格制作游戏布局。  
绘制游戏边界使用了ANSI控制码，其详细信息参考：https://gist.github.com/fnky/458719343aabd01cfb17a3a4f7296797  
不同类型的方块命名，游戏方式参考网站：https://harddrop.com/wiki/Tetris_Wiki  
