# Pwnlib

*Based on C++ binary file analysis and CTF pwn utilization code generation framework. *
*have fun!*

![label1](https://img.shields.io/badge/build-passing-COLOR)
[![label2](https://img.shields.io/badge/author-migraine-blue)](https://migraine-sudo.github.io/)
[![label3](https://img.shields.io/badge/yaml--cpp-0.6.0-orange)](https://github.com/jbeder/yaml-cpp)


## Introduction

Based on the C++11 standard under the Linux platform, a quick utilization script is generated for the heap utilization problem in CTF pwn.

The program is still under development and currently contains two modes, Half_Auto_Mod and Auto_Mod.

- The former requires the user to fill in the corresponding input for the menu, and after the complete menu function is over, enter finish to help the program determine the end of a cycle, and then enter quit to complete the entire program.

- The latter is the automatic completion of program analysis and script generation. It is due to the binary file. The accuracy varies from question to question. Below is a demonstration of the usage of these two modes and a simple tutorial.


Run screenshot

![NazPPS](https://gitee.com/p0kerface/blog_image_management/raw/master/uPic/NazPPS.png)


![AVN4rO](https://gitee.com/p0kerface/blog_image_management/raw/master/uPic/AVN4rO.png)



**Tutorial**

Use automatic mode for analysis

1. Prepare the test program (test/test)

![test](https://media.giphy.com/media/5LLDTPnZ3TeEca9a4F/giphy.gif)

2. Automated analysis

![analyse](https://media.giphy.com/media/5qXrOZpVNgHcaGxSho/giphy.gif)

3. Generate script display (the accuracy of automatic mode is still lacking, you can choose manual mode)

![CS24hx](https://gitee.com/p0kerface/blog_image_management/raw/master/uPic/CS24hx.png)


Use manual mode for analysis



## How to build the project

**Compile the main program**

You need to write relevant code in main.cc to quickly customize a pwn problem-solving script.

It is recommended to add the program path to the PATH environment variable after the compilation is completed to facilitate analysis in all directories.

```make ```

**Compile Demo**

1. Debug version automatic analysis (fast but the accuracy varies from question to question)

```make demo_auto_debug```

2. Debug version semi-automatic analysis (relatively stable)

```make demo_half_auto_debug```

3. Release version automatic analysis

```make demo_auto_release```


## Development Document

**How ​​to use the framework to write code? => [Tutorial]()**

### PWN

Header file directory: ***/include/pwnlib.h***

Provides the core methods of the core PWN framework, including but not limited to loading binary programs, receiving interactive output, sending interactive data, calling Parse_Mode module for automated analysis, script generation and other functions.

*Current version function display*

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

Header file directory: ***/include/parse.h***

The auxiliary analysis module is embedded in the PWN class as a **template parameter**, and provides analysis logic support for the analyze function of the PWN module. Users can reload the functions recv_(), send_() to better analyze logic for programming accuracy/automation.

**Half Auto Mod**

The semi-automatic mode requires the user to interact with the program using **pwnlib shell**. Parameter introduction

**help or h**: Print help parameters.

**finish or f**: When an input loop is completed (that is, when returning to the start menu), enter finish as a mark to help the program determine whether a loop is over. *Of course, my AI will also remind you if she works well. *

**quit or q**: complete the analysis and proceed to the next step (script generation).

>Warning: In the semi-automatic mode, if you do not use the Debug parameter to compile, you will not see interactive information when running the program. Of course, the program will prompt you to provide compilation options, as shown in the figure

![EPLKkx](https://gitee.com/p0kerface/blog_image_management/raw/master/uPic/EPLKkx.png)

**Auto Mod**

Fully automated analysis mode, no need to interact with binary files, the program automatically analyzes the feedback data to guess the current execution progress, and is still working hard to improve accuracy.

### Print

Provide some own output methods

### MString

Provide some own String operation methods


## Update progress

**v0.0.3(2021.2.22)**
- Develop yaml custom configuration exploit based on yaml-cpp (30% progress)

**v0.0.2(2021.2.18)**
- Added Mstring.h library to provide some own String methods
- Add Traverse_string to increase the judgment accuracy of the automatic module

**v0.0.1(2021.2.17)**
- Project creation, edit README
- Create demo section


## Need to improve

- The software structure is more complicated, especially the coupling between PWN and Parse_Mod modules is very high (the reason is that I wanted to improve the scalability through Parse_Mod at the beginning, but the result increased the complexity of the PWN module).
- Currently there is no support for yaml file customization of exploit scripts. (Added, added)
- FUZZ mode has not been developed yet, it is expected to automatically generate poc
- The use of Unicorn to run ELF of other architectures is not yet supported
- The source code directory needs to be adjusted (many core codes are still written in the header file)