// g++ main.cc --std=c++11 -D__DEBUG__
/*
A C++-based binary file analysis and CTF pwn 
exploit code generation framework.
Have fun!
Author : Migraine-sudo
*/

#include "pwnlib.h"
#include "parse.h"
#include "print.h"
#include <iostream>
#include <string>
using namespace std;
string exec_path;

int main()
{
    PWN<Auto_Mod> *p = new PWN<Auto_Mod>(string("../bin/test"));
    p->analyze_manual_();
}