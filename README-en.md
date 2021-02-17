# pwnlib

*Author : Migraine-sudo*

*A C++-based binary file analysis and CTF pwn exploit code generation framework.*
*Have fun!*

## Introduction
Based on the C++11 standard under the Linux platform, it provides a quick exploit script for menu questions in CTF pwn.

The program is still under development and currently contains two modes, Half_Auto_Mod and Auto_Mod.The former requires the user to fill in the corresponding input for the menu, and after a complete menu function is over, input finish to help the program determine the end of a cycle, and input quit to complete the entire program.The latter is to complete the program analysis and script generation automatically, but the accuracy is easy due to the binsi.Below is a demonstration of the use of the two modes and a simple tutorial.

**Tutorial**



## How to Comiple

Release Mode
```g++ main.cc --std=c++11```

Debug Mode
```g++ main.cc --std=c++11 -D__DEBUG__```

## PWN



## Parse_Mode

### Half Auto Mod


>Warning: In the semi-automatic mode, if you do not use the Debug parameter to compile, you will not see interactive information when running the program.Of course, the program will prompt for compilation options, as shown in the figure


![EPLKkx](https://gitee.com/p0kerface/blog_image_management/raw/master/uPic/EPLKkx.png)


## Print


