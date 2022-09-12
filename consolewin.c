//ConsoleWindow
//“ConsoleWindow”是一个帮助你在cmd绘制窗口的库。
//项目地址:                		https://github.com/the-cat1/ConsoleWindow
//项目最后上传时间:         	2022/9/10
//项目版本:                 	Version 1.0
//By the-cat1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "consolewin.h"

void DrawWindow(Window window) {
    printf("\033[%i;%im\033(0", window.fc, window.bc);
    
    //画四个角
    GOTO(window.dx, window.dy);                       putchar('l');
    GOTO(window.dx + window.x, window.dy);            putchar('k');
    GOTO(window.dx + window.x, window.dy + window.y); putchar('j');
    GOTO(window.dx, window.dy + window.y);            putchar('m');

    //画四条边
    for (int i = 1; i < window.x; i++) {        //上面
        GOTO(window.dx + i, window.dy);
        putchar('q');
    }
    for (int i = 1; i < window.x; i++) {        //下面
        GOTO(window.dx + i, window.dy + window.y);
        putchar('q');
    }
    for (int i = 1; i < window.y; i++) {        //左边
        GOTO(window.dx, window.dy + i);
        putchar('x');
    }
    for (int i = 1; i < window.y; i++) {        //右边
        GOTO(window.dx + window.x, window.dy + i);
        putchar('x');
    }

    //画里面
    for (int fy = 1; fy < window.y; fy++) {
        for (int fx = 1; fx < window.x; fx++) {
            GOTO(window.dx + fx, window.dy + fy);
            putchar(' ');
        }
    }
    
    printf("\033(B\033[0m");

    HANDLE outputHand = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD getWrittenCount = 0;
    COORD writtenPos = {window.dx, window.dy + window.y};
    FillConsoleOutputAttribute(outputHand, 0x8F, window.x, writtenPos, &getWrittenCount);

    writtenPos.X = window.dx + window.x;
    for (int i = 0; i < window.y + 1; i++) {
        writtenPos.Y = i + window.dy;
        FillConsoleOutputAttribute(outputHand, 0x8F, 1, writtenPos, &getWrittenCount);
    }
    
}

void CenterWindow(Window* window) {
    HANDLE outputHand = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    GetConsoleScreenBufferInfo(outputHand, &consoleInfo);
    
    int X = (consoleInfo.srWindow.Right + 1) / 2 - window->x / 2;
    int Y = (consoleInfo.srWindow.Bottom + 1) / 2 - window->y / 2;
    window->dx = X;
    window->dy = Y;
}

void DrawAText(Text text, Window* window) {
    if (window == NULL || !text.window) {
        GOTO(text.dx, text.dy);
        printf("\033[%i;%im%s\033[0m", text.fc, text.bc, text.text);
    }else{       
        GOTO(text.dx + window->dx, text.dy + window->dy);
        printf("\033[%i;%im%s\033[0m", window->fc, window->bc, text.text);
    }
}

void CenterText(Text* text, CenterMode centermode, Window* window) {
    if (text->window) {
        //在窗口里居中
        if (window == NULL) {
            printf("ConsoleWindowError:文字的窗口指针为空!");
            getchar();
            exit(-1);
        }

        if (centermode & X_Center) {
            int textlen = (int)strlen(text->text);
            int X = window->x / 2 - textlen / 2;
            text->dx = X;
        }
        if (centermode & Y_Center) {
            int Y = window->y / 2;
            text->dy = Y;
        }
        
    }else{
        //在屏幕上居中
        HANDLE outputHand = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
        GetConsoleScreenBufferInfo(outputHand, &consoleInfo);
        
        if (centermode & X_Center) {
            int textlen = (int)strlen(text->text);
            int X = (consoleInfo.srWindow.Right + 1) / 2 - textlen / 2;
            text->dx = X;
        }
        if (centermode & Y_Center) {
            int Y = (consoleInfo.srWindow.Bottom + 1) / 2;
            text->dy = Y;
        }
    }
}

void DrawButton(Button button, Window* window) {
    if (window == NULL) {
        printf("ConsoleWindowError:按钮的窗口为空!");
        getchar();
        exit(-1);
    }

    GOTO(button.dx + window->dx, button.dy + window->dy);

    printf("\033[%i;%im", button.fc, button.bc);
    if (button.isSelet) { printf("\033[%im", button.selet); }
    printf("%s\033[0m", button.text);
}

void CenterButton(Button* button, CenterMode centermode, Window* window, _BOOL onDown) {
    if (window == NULL) {
        printf("ConsoleWindowError:按钮缺少父Window!");
        getchar();
        exit(-1);
    }

    if (centermode & X_Center) {
        int textlen = strlen(button->text);
        int X = window->x / 2 - textlen / 2;
        button->dx = X;
    }
    if (centermode & Y_Center) {
        int Y = window->y;
        if (onDown) {
            Y -= 1;
        }else{
            Y /= 2;
        }
        button->dy = Y;
    }
}

void DrawProgress(Progress progress, int larp, Window* window, int s) {
    if (window == NULL) {
        printf("ConsoleWindowError:进度条缺少父Window!");
        getchar();
        exit(-1);
    }
    
    GOTO(progress.dx + window->dx, progress.dy + window->dy);
    
    printf("\033[%i;%im", progress.fc, progress.bc);
    for (int i = 0; i < larp / s; i++) { putchar(' '); }
    printf("\033[0m");
}

void DrawLongText(LongText longtext, Window* window) {
    int drawStartX = 0;
    int drawStartY = 0;
    int fcolor     = 0;
    int bcolor     = 0;
    if (window == NULL || !longtext.window) {
        drawStartX = 1;
        drawStartY = 1;
        fcolor     = longtext.fc;
        bcolor     = longtext.bc;
    }else{
        drawStartX = window->dx + longtext.dx;
        drawStartY = window->dy + longtext.dy;
        fcolor     = window->fc;
        bcolor     = window->bc;
    }
    
    printf("\033[%i;%im", fcolor, bcolor);
    int l = 0;
    
    GOTO(drawStartX, drawStartY);
    for (int i = 0; i < strlen(longtext.text); i++) {
        if (longtext.text[i] == '\n') {
            l++;
            GOTO(drawStartX, drawStartY + l);
        }else{
            putchar(longtext.text[i]);
        }
    }
    
    printf("\033[0m");
}
