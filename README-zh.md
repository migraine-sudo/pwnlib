# pwnlib

*作者: Migraine-sudo*

*基于C ++的二进制文件分析和CTF pwn利用代码生成框架。*
*玩得开心!*

## Introduction

它基于Linux平台下的C ++ 11标准，为CTF pwn中的堆利用题目生成一个快速利用脚本。

该程序仍在开发中，目前包含Half_Auto_Mod和Auto_Mod这两种模式，前者需要用户为菜单填写相应的输入，并且在完整的菜单功能结束后，输入finish以帮助程序确定结束一个周期，然后输入quit以完成整个程序。后者是自动完成程序分析和脚本生成，是由于binsi的原因，准确性很容易。下面是这两种模式的用法演示和一个简单的教程。

**Tutorial**



## How to Comiple

Release Mode
```g++ main.cc --std=c++11```

Debug Mode
```g++ main.cc --std=c++11 -D__DEBUG__```

## PWN



## Parse_Mode

### Half Auto Mod



警告：在半自动模式下，如果不使用Debug参数进行编译，则在运行程序时将看不到交互信息。当然，程序会提示您提供编译选项，如图所示

![EPLKkx](https://gitee.com/p0kerface/blog_image_management/raw/master/uPic/EPLKkx.png)


## Print

