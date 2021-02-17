# Pwnlib

*作者: Migraine-sudo*

*基于C ++的二进制文件分析和CTF pwn利用代码生成框架。*
*玩得开心!*

![label1](https://img.shields.io/badge/build-makefile-COLOR)
[![label2](https://img.shields.io/badge/author-migraine-blue)](https://migraine-sudo.github.io/)
[README-En](https://github.com/migraine-sudo/pwnlib/blob/main/README-en.md)

## Introduction

它基于Linux平台下的C ++ 11标准，为CTF pwn中的堆利用题目生成一个快速利用脚本。

该程序仍在开发中，目前包含Half_Auto_Mod和Auto_Mod这两种模式，前者需要用户为菜单填写相应的输入，并且在完整的菜单功能结束后，输入finish以帮助程序确定结束一个周期，然后输入quit以完成整个程序。后者是自动完成程序分析和脚本生成，是由于二进制文件的原因，准确性因题而异。下面是这两种模式的用法演示和一个简单的教程。

**Tutorial**



## 如何构建项目

**编译主程式**
需要在main.cc中调用pwnlib提供的框架，快速自定义一个pwn解题脚本
```make ```

**编译Demo**
1.Debug版自动分析（快速但是精确度因题而异）
```make demo_auto_debug```
2.Debug版半自动分析(比较稳定)
```make demo_half_auto_debug```
3.Release版自动分析
```make demo_auto_release```

## PWN



## Parse_Mode

### Half Auto Mod



警告：在半自动模式下，如果不使用Debug参数进行编译，则在运行程序时将看不到交互信息。当然，程序会提示您提供编译选项，如图所示

![EPLKkx](https://gitee.com/p0kerface/blog_image_management/raw/master/uPic/EPLKkx.png)


## Print




## 更新进度



## 需改进点

- 软件结构比较复杂，特别是PWN和Parse_Mod模块两者耦合度很高（原因在于一开始想通过Parse_Mod提高可扩展性,结果反而增加了PWN模块的复杂度）。
- 目前害不支持yaml格式的exploit脚本自定义。（在加了，在加了）
