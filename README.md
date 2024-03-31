# ConsoleWindow
## 项目简介
“ConsoleWindow”是一个可以在cmd中绘制窗口的库。不过，只能**绘制**窗口，原生不能进行交互。现在支持以下控件:

- Window:窗口
- Text:文本
- Button:按钮
- LongText:长文本(字面意思)
- Progress:进度条

> 注意:本库用到了`windows.h`，因此只能在`Windows NT`上运行。

## Demo
### 1.Window
十分简单的Demo。开始会让你下载什么文件，就像平时下载文件一样，卡在99%...最后就是——Creeper?

![window-image-1](./Image/window-1.png)
![window-image-2](./Image/window-2.png)
![window-image-1](./Image/window-3.png)
![window-image-2](./Image/window-4.png)

> Byd 我 man 还拼错了

### 2.YourDosInstaller
这个Demo有一点长，不过还是很简单。这是一个安装程序，安装时可以按`Ctrl+方向键`来改变窗口位置，`左方向键`选择`Exit`，`右方向键`选择`Install`，`空格`和`回车`按下选择的按钮。安装完成之后，打开一看：先是营销号一般的操作(自信点，就是 ~~营销号~~ 某黑客)，然后启动了...是Window自带的cmd!

![YourDosInstaller-1](./Image/YourDosInstaller-1.png)
![YourDosInstaller-2](./Image/YourDosInstaller-2.png)
![YourDosInstaller-3](./Image/YourDosInstaller-3.png)
![YourDosInstaller-4](./Image/YourDosInstaller-4.png)
![YourDosInstaller-5](./Image/YourDosInstaller-5.png)

生成的.bat文件。

![运行后-1](./Image/YourDosInstaller-bat-1.png)
![运行后-2](./Image/YourDosInstaller-bat-2.png)
![运行后-3](./Image/YourDosInstaller-bat-3.png)
![生成的.bat文件](./Image/YourDosInstall-bat-file.png)

> 要卸载的话，直接把桌面上的`YourDos.bat`扔进回收站就行了。<br>
> 还有，我 TM 忘记加项目地址了！

## 后
当初写这个库的时候，VSCode误报一大堆，但是现在更新了，写 Win32api 应该不错 :) 。

我注释也没写多少，以后再补吧...
