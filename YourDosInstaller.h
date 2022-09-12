//YourDosInstall
//基于“ConsoleWindow”的一个Demo。
//“ConsoleWindow”项目地址:		https://github.com/the-cat1/ConsoleWindow
//开始制作时间:            		2022/8/29(左右)
//最后修改时间:          	    2022/9/10
//By the-cat1

#ifndef __YOUR_DOS_INSTALLER__
#define __YOUR_DOS_INSTALLER__
#define START_COMMAND           "CHCP 65001 && MODE CON LINES=%i COLS=%i && COLOR 17 && CLS"
#define RESTART_COMMAND         "COLOR 17 && MODE CON LINES=%i COLS=%i && CLS"
#define END_COMMAND             "start YourDos.bat && cls"

#define START_CHARS             110
#define START_LINES             40
#define MAIN_WINDOW_X           50
#define MAIN_WINDOW_Y           20
#define MAIN_WINDOW_INSTALL_X   53
#define MAIN_WINDOW_INSTALL_Y   2	
#define EXIT_APP_WINDOW_X       32
#define EXIT_APP_WINDOW_Y       6
#define BUTTON_SELET_STYLE      4

#define PRINT_MESSAGE           "\033[37;44m[%s]:%s\n\033[0m"
#define INPUT_CHOOSE            "\033[37;44m[Input]:%s>\033[0m"
#define START_MESSAGE1          "欢迎来到“YourDos”安装程序!"
#define START_MESSAGE2          "按下“\033[33mY\033[37;44m”以继续安装,“\033[33mN\033[37;44m”以退出安装。"
#define START_INPUT1            "输入选择"
#define END_INSTALL_MESSAGE     "退出安装..."
#define START_INSTALL_MESSAGE   "继续安装..."
#define INIT_MESSAGE            "正在初始化安装程序..."
#define INIT_OK_MESSAGE         "初始化完成!"
#define INSTALL_FILENAME        "C:\\Users\\Public\\Desktop\\YourDos.bat"
#define INSTALL_C_N_C_FILE      "安装失败 - 无法创建文件"
#define INSTALL_TITLE           "正在安装YourDos...(%i%%)"
#define INSTALL_END_TITLE       "按任意键退出安装程序"

//标题
#define TITLE                   "\033[37;44m====================\n"\
                                "YourDos Installer\n"\
                                "====================\033[0m\n"

//安装须知
#define LICENSE                 "本程序只供测试和演示!\n"\
                                "所用到的库是“ConsoleWindow”。\n\n"\
                                "项目地址:           |https:\\\\\n"/*TODO:项目地址on LICENSE*/\
                                "本程序创建时间:     |2022/8/29(左右)\n"

//退出信息
#define EXIT_APP_TEXT           "YourDos未完成安装!\n"\
                                "是否退出?(Y:退出,N:继续)"

//骗人的脚本(凑齐100个字符)
#define BAT_SCRIPT             "@echo off\n"\
                                "chcp 65001\n"\
                                "title YourDos\n"\
                                "tree C:\\Windows\n"\
                                "title 操作已完成!\n"\
                                "timeout 3\n"\
                                "start cmd\n"\
                                "exit\n"

#define ExitBeep Beep(300, 500)                  //退出声
#define TipsBeep Beep(800, 100)                  //提示声
#endif
