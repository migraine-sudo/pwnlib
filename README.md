# Pwnlib

*基于C ++的二进制文件分析和CTF pwn利用代码生成框架。*
*玩得开心!*

![label1](https://img.shields.io/badge/build-passing-COLOR)
[![label2](https://img.shields.io/badge/author-migraine-blue)](https://migraine-sudo.github.io/)
[![label3](https://img.shields.io/badge/yaml--cpp-0.6.0-orange)](https://github.com/jbeder/yaml-cpp)


[README-En](https://github.com/migraine-sudo/pwnlib/blob/main/README-en.md)

## 简介

基于Linux平台下的C++11标准，为CTF pwn中的堆利用题目生成一个快速利用脚本。

该程序仍在开发中，目前包含Half_Auto_Mod和Auto_Mod这两种模式。

- 前者需要用户为菜单填写相应的输入，并且在完整的菜单功能结束后，输入finish以帮助程序确定结束一个周期，然后输入quit以完成整个程序。

- 后者是自动完成程序分析和脚本生成，是由于二进制文件的原因，准确性因题而异。下面是这两种模式的用法演示和一个简单的教程。


运行截图

![NazPPS](https://gitee.com/p0kerface/blog_image_management/raw/master/uPic/NazPPS.png)


![AVN4rO](https://gitee.com/p0kerface/blog_image_management/raw/master/uPic/AVN4rO.png)



**教程**

使用自动模式进行分析

1. 准备好测试程序（test/test）

![test](https://media.giphy.com/media/5LLDTPnZ3TeEca9a4F/giphy.gif)

2. 自动化分析

![analyse](https://media.giphy.com/media/5qXrOZpVNgHcaGxSho/giphy.gif)

3. 生成脚本展示(自动模式精准度还有欠缺，可以选择手动模式)

![CS24hx](https://gitee.com/p0kerface/blog_image_management/raw/master/uPic/CS24hx.png)


使用手动模式进行分析



## 如何构建项目

**编译主程式**

需要在main.cc中编写相关代码，快速自定义一个pwn解题脚本。

建议在编译完成之后将程序路径添加到PATH环境变量，方便在所有目录下进行分析。

```make ```

**编译Demo**

1.Debug版自动分析（快速但是精确度因题而异）

```make demo_auto_debug```

2.Debug版半自动分析(比较稳定)

```make demo_half_auto_debug```

3.Release版自动分析

```make demo_auto_release```


## 开发文档

**如何使用框架来编写代码？=> [Tutorial]()**

### PWN

头文件目录：***/include/pwnlib.h***

提供核心PWN框架的核心方法，包括但不限于加载二进制程序、接收交互输出、发送交互数据、调用Parse_Mode模块自动化分析、脚本生成等功能。

*目前版本函数展示*

```
    bool load_();
    char *recv_();
    char *recv_line_();
    bool send_(string str);
    bool send_line_(string str);
    void analyze_();
    void analyze_manual_();
    void show_node_list_();
    void gengerate_();
    void gengerate_(string file_name);
```


### Parse_Mode

头文件目录：***/include/parse.h***

辅助分析模块，作为**模板参数**嵌入PWN类中，为PWN模块的analyse函数提供分析逻辑支持。使用者可以通过重载函数recv_(),send_()，为程序编准确度/自动化更好的分析逻辑。

**Half Auto Mod**

半自动模式，需要用户使用**pwnlib shell**与程序进行交互。参数介绍

**help 或者 h** : 打印帮助参数。

**finish 或者 f** : 当一次输入循环完成（即回到开始菜单的时候），输入finish作为标记，帮助程序判断是否一次循环结束。*当然，我的AI也会提醒您，如果她运转良好的话。*

**quit 或者 q** : 完成分析，进入下一步操作（脚本生成）。

>警告：在半自动模式下，如果不使用Debug参数进行编译，则在运行程序时将看不到交互信息。当然，程序会提示您提供编译选项，如图所示

![EPLKkx](https://gitee.com/p0kerface/blog_image_management/raw/master/uPic/EPLKkx.png)

**Auto Mod**

全自动化分析模式，不需要和二进制文件进行交互，通过程序自动分析反馈数据来猜测当前执行进度，仍然在为了提高精确度而不断努力中。

### Print

提供一些自己的输出方法

### MString

提供一些自己的String操作方法


## 更新进度

**v0.0.3(2021.2.22)**
- 基于yaml-cpp开发yaml自定义配置exploit(进度30%)

**v0.0.2(2021.2.18)**
- 增加Mstring.h库提供一些自己的String方法
- 增加Traverse_string来增加自动模块的判断准确度

**v0.0.1(2021.2.17)**
- 项目创建，编辑README
- 创建演示部分


## 需改进点

- 软件结构比较复杂，特别是PWN和Parse_Mod模块两者耦合度很高（原因在于一开始想通过Parse_Mod提高可扩展性,结果反而增加了PWN模块的复杂度）。
- 目前还不支持yaml文件对exploit脚本自定义。（在加了，在加了）
- FUZZ模式还没开发，预计能够自动生成poc
- 还不支持使用Unicorn来运行其他架构的ELF 
- 源代码目录需要调整（现在很多核心代码都还写在头文件中）
