#ifndef __CONSOLEWIN__
#define __CONSOLEWIN__ "1.0"

//Bool类型    
#define _True 1
#define _False 0

//Center模式定义
#define X_Center         0b00000001          //对于x居中
#define Y_Center         0b00000010          //对于y居中

//常量定义
#define TEXT_MAX_LEN 32                      //文字的最大长度
#define BUTTON_TEXT_MAX_LEN 16               //按钮文字的最大长度
#define LONG_TEXT_MAX_LEN 512                //文字的最大长度

//去屏幕上的某个字符
#define GOTO(x,y) printf("\033[%i;%iH",y,x)


/*定义类型*/
typedef int _BOOL;                           //布尔类型
typedef int CenterMode;                      //居中模式


/*定义结构体类型*/
//窗口
struct _Window {
    int dx;                                  //窗口的x坐标
    int dy;                                  //窗口的y坐标
    int x;                                   //窗口的长度
    int y;                                   //窗口的宽度
    int fc;                                  //前景色
    int bc;                                  //背景色
};

//文字
struct _Text {
    int dx;                                  //文字的x坐标
    int dy;                                  //文字的y坐标
    char text[TEXT_MAX_LEN];                 //文字
    int fc;                                  //前景色
    int bc;                                  //背景色
    _BOOL window;                            //是否继承Window的颜色
};

//长文本
struct _LongText {
    int dx;                                  //长文本的x坐标
    int dy;                                  //长文本的y坐标
    char text[LONG_TEXT_MAX_LEN];            //文字
    int fc;                                  //前景色
    int bc;                                  //背景色
    _BOOL window;                            //是否继承Window的颜色
};

//按钮
struct _Button {
    int dx;
    int dy;
    char text[BUTTON_TEXT_MAX_LEN];
    int fc;                                  //前景色
    int bc;                                  //背景色
    int selet;                               //选中的效果
    _BOOL isSelet;
};

//进度条
struct _Progress {
    int dx;                                  //x坐标
    int dy;                                  //y坐标
    int fc;                                  //前景色
    int bc;                                  //背景色
};


/*struct类*/
typedef struct _Window   Window;             //窗口
typedef struct _Text     Text;               //文字
typedef struct _Button   Button;             //按钮
typedef struct _Progress Progress;           //进度条
typedef struct _LongText LongText;           //长文本


/*声明函数*/
void DrawWindow(Window window);
void CenterWindow(Window* window);
void DrawAText(Text text, Window* window);
void CenterText(Text* text, int centermode, Window* window);
void DrawButton(Button button, Window* window);
void CenterButton(Button* button, CenterMode centermode, Window* window, _BOOL onDown);
void DrawProgress(Progress progress, int larp, Window* window, int s);
void DrawLongText(LongText longtext, Window* window);
#endif
