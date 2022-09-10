//YourDosInstall
//基于“ConsoleWindow”的一个Demo。
//“ConsoleWindow”项目地址://TODO:地址
//开始制作时间:              2022/8/29(左右)
//最后修改时间:              2022/9/10

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include "consolewin.h"
#include "YourDosInstaller.h"

int MessagePos = 1;                                            //消息位置

//打印信息
void PrintMessage(char type[8], char mag[64]) {
    GOTO(1, MessagePos);
    printf(PRINT_MESSAGE, type, mag);
    MessagePos++;
}

//打印标题
void PrintTitle() {
    GOTO(1, 1);
    puts(TITLE);
    MessagePos = 5;
}

//输入选择
int InputChoose(char mag[32]) {
    printf(INPUT_CHOOSE, mag);
    return getch();
}

//退出程序
void ExitApp(Window exitAppWindow) {
    DrawWindow(exitAppWindow);
    LongText exitAppText = {
        .dx = 1,
        .dy = 1,
        .text = EXIT_APP_TEXT,
        .window = _True
    };
    DrawLongText(exitAppText, &exitAppWindow);
    
    int c = getch();
    if (c == 'Y' || c == 'y') { ExitBeep; exit(0); }
}


int main(int argc, char const *argv[])
{
    /*运行命令*/
    char command[64];
    sprintf(command, START_COMMAND, START_LINES, START_CHARS);
    system(command);
    printf("\033[?25l");

    /*用户选择是否安装*/
    PrintTitle();
    PrintMessage("INFO", START_MESSAGE1);
    PrintMessage("INFO", START_MESSAGE2);
    int input = InputChoose(START_INPUT1);
    if (input != 'y' && input != 'Y') {
        PrintMessage("INFO", END_INSTALL_MESSAGE);
        ExitBeep;
        return 0;
    }
    PrintMessage("INFO", START_INSTALL_MESSAGE);
    PrintMessage("INFO", INIT_MESSAGE);

    /*初始化*/
    sprintf(command, RESTART_COMMAND, START_LINES, START_CHARS);

    Window   MainWindow      = {
        .x  = MAIN_WINDOW_X,
        .y  = MAIN_WINDOW_Y,
        .dx = 0,
        .dy = 0,
        .fc = 30,
        .bc = 47
    };
    Text     MainWindowTitle = {
        .dy = 0,
        .text = "YourDos安装程序",
        .window = _True
    };
    Window   ExitAppWindow   = {
        .x = EXIT_APP_WINDOW_X,
        .y = EXIT_APP_WINDOW_Y,
        .dx = 0,
        .dy = 0,
        .fc = 36,
        .bc = 47
    };
    LongText LicenseLongText = {
        .dx = 1,
        .dy = 1,
        .text = LICENSE,
        .window = _True
    };
    Button   InstallButton   = {
        .dx = 41,
        .dy = 18,
        .selet = BUTTON_SELET_STYLE,
        .fc = 30,
        .bc = 46,
        .text = "Install",
        .isSelet = _True
    };
    Button   ExitButton      = {
        .dx = 2,
        .dy = 18,
        .selet = BUTTON_SELET_STYLE,
        .fc = 30,
        .bc = 41,
        .text = "Exit",
        .isSelet = _False
    };
    Progress WriteProgress   = {
        .dx = 2,
        .dy = MAIN_WINDOW_INSTALL_Y - 1,
        .fc = 37,
        .bc = 43
    };

    CenterWindow(&MainWindow);
    CenterWindow(&ExitAppWindow);
    CenterText(&MainWindowTitle, X_Center, &MainWindow);

    /*初始化完成*/
    PrintMessage("INFO", INIT_OK_MESSAGE);
    TipsBeep;
    system(command);

    /*绘制*/
    PrintTitle();
    DrawWindow(MainWindow);
    DrawAText(MainWindowTitle, &MainWindow);
    DrawLongText(LicenseLongText, &MainWindow);
    DrawButton(InstallButton, &MainWindow);
    DrawButton(ExitButton, &MainWindow);

    /*安装须知*/
    int c;                                                     //用户输入
    _BOOL updateWindow;                                        //更新窗口
    _BOOL install = _False;                                    //是否安装
    while (_True) {
        updateWindow = _False;

        /*判断按下按键*/
        c = getch();
        switch (c)
        {
        case 0:
            //退出?
            c = getch();
            //Alt+F4
            if (c = 107) { ExitApp(ExitAppWindow); updateWindow = _True; }
            break;

        case 224:
            //方向键
            c = getch();
            switch (c)
            {
            case 75:
                //<- 选择Exit按钮
                InstallButton.isSelet = _False;
                ExitButton.isSelet     = _True;
                break;

            case 77:
                //-> 选择Continue按钮
                InstallButton.isSelet = _True;
                ExitButton.isSelet     = _False;
                break;

            case 141:
                //窗口上移
                if (MainWindow.dy < 2) {
                    TipsBeep;
                }else{
                    updateWindow = _True;
                    MainWindow.dy--;
                }
                break;

            case 145:
                //窗口下移
                if (MainWindow.dy > START_LINES - MAIN_WINDOW_Y - 2) {
                    TipsBeep;
                }else{
                    updateWindow = _True;
                    MainWindow.dy++;
                }
                break;
            
            case 115:
                //窗口左移
                if (MainWindow.dx < 2) {
                    TipsBeep;
                }else{
                    updateWindow = _True;
                    MainWindow.dx--;
                }
                break;
                
            case 116:
                //窗口右移
                if (MainWindow.dx > START_CHARS - MAIN_WINDOW_X - 2) {
                    TipsBeep;
                }else{
                    updateWindow = _True;
                    MainWindow.dx++;
                }
                break;

            default:
                break;
            }
            break;
        
        case ' ':                                //空格
        case 13:                                 //回车
            //按下按键
            if (ExitButton.isSelet) {
                //退出
                ExitApp(ExitAppWindow);
                updateWindow = _True;
            }else{
                //继续安装
                install = _True;
            }
            break;

        default:
            break;
        }

        if (install) {
            //确认安装
            system(command);
            break;
        }
        
        /*更新屏幕*/
        if (updateWindow) {
            //更新窗口
            system(command);
            PrintTitle();
            DrawWindow(MainWindow);
            DrawAText(MainWindowTitle, &MainWindow);
            DrawLongText(LicenseLongText, &MainWindow);    
        }
        //绘制按钮
        DrawButton(InstallButton, &MainWindow);
        DrawButton(ExitButton, &MainWindow);
    }

    /*安装*/
    FILE* bat = fopen(INSTALL_FILENAME, "w");                  //写入文件
    char script[100] = BAT_SCRIPT;                             //要写入的数据
    char tmp[32];                                              //临时字符串

    //设置窗口x、y大小并绘制窗口
    MainWindow.x = MAIN_WINDOW_INSTALL_X;
    MainWindow.y = MAIN_WINDOW_INSTALL_Y;
    if (bat == NULL) {
        //打开文件失败
        strcpy(MainWindowTitle.text, INSTALL_C_N_C_FILE);
        CenterWindow(&MainWindow);
        CenterText(&MainWindowTitle, X_Center, &MainWindow);

        PrintTitle();
        DrawWindow(MainWindow);
        
        getch();

        return -1;
    }
    CenterWindow(&MainWindow);
    CenterText(&MainWindowTitle, X_Center, &MainWindow);
    PrintTitle();
    DrawWindow(MainWindow);

    //慢悠悠地写入数据
    for (int i = 0; i < 100; i++) {
        putc(script[i], bat);

        sprintf(tmp, INSTALL_TITLE, i);
        strcpy(MainWindowTitle.text, tmp);
        CenterText(&MainWindowTitle, X_Center, &MainWindow);
        DrawAText(MainWindowTitle, &MainWindow);
        DrawProgress(WriteProgress, i, &MainWindow, 2);
        Sleep(10);
    }

    fclose(bat);
    
    //结束安装
    strcpy(MainWindowTitle.text, INSTALL_END_TITLE);
    CenterWindow(&MainWindow);
    CenterText(&MainWindowTitle, X_Center, &MainWindow);
    PrintTitle();
    DrawWindow(MainWindow);
    DrawAText(MainWindowTitle, &MainWindow);
    
    getch();
    system(END_COMMAND);
    printf("\033[?25h");
    
    return 0;
}
