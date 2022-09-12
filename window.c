//Window
//基于“ConsoleWindow”的一个Demo。
//“ConsoleWindow”项目地址:   	https://github.com/the-cat1/ConsoleWindow
//开始制作时间:              	2022/8/24~2022/8/27
//最后修改时间:              	2022/9/10
//By the-cat1

#include <conio.h>
#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include "consolewin.h"

int main(int argc, char const *argv[])
{
    system("chcp 65001 && CLS");
    printf("\033[?25l");

    Window   window = {
        0,                     //窗口x位置(等会居中窗口)
        0,                     //窗口y位置(等会居中窗口)
        32,                    //窗口长度
        7,                     //窗口高度
        37,                    //前景色
        46                     //背景色
    };
    Window   progressWindow = {
        0,
        0,
        50,
        2,
        37,
        45
    };
    Text     text = {
        10,
        10,
        "下载^$#@$*&(#!%%^#<>:;\"",
        0,
        0,
        _True
    };
    Text     creepertext = {0, 0, "Creeper?Oh may!", 0, 0, _True};
    Button   button = {
        1,
        7,
        "[下载]",
        37,
        46,
        7,
        _True
    };
    Progress progress = {
        1,
        1,
        37,
        43
    };

    CenterWindow(&window);
    CenterWindow(&progressWindow);

    CenterText(&text, X_Center | Y_Center, &window);

    CenterButton(&button, X_Center | Y_Center, &window, _True);

    DrawWindow(window);
    DrawAText(text, &window);
    DrawButton(button, &window);
    
    while (_True) {
        int c;
        c = getch();
        if (c == 13 || c == ' ') {
            break;
        }
    }

    DrawWindow(progressWindow);
    Text progtext = { 1, 0, "Hi!", 0, 0, _True };

    for (int i = 0; i < 100; i++) {
        char ci[TEXT_MAX_LEN];
        sprintf(ci, "%i%%", i);
        strcpy(progtext.text, ci);

        CenterText(&progtext, X_Center, &progressWindow);
        DrawAText(progtext, &progressWindow);
        DrawProgress(progress, i, &progressWindow, 2);
        Sleep(100);
        if (i == 99)
            Sleep(9000);
    }
    
    system("CLS");
    strcpy(button.text, "[按Enter退出]");
    CenterButton(&button, X_Center, &window, _True);
    CenterText(&creepertext, X_Center | Y_Center, &window);
    DrawWindow(window);
    DrawAText(creepertext, &window);
    DrawButton(button, &window);
    getch();
    
    printf("\033[?25h");
    return 0;
}
