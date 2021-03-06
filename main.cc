// g++ main.cc --std=c++11 -D__DEBUG__
/*
A C++-based binary file analysis and CTF pwn 
exploit code generation framework.
Have fun!
Author : Migraine-sudo
*/
/*
#include "source/pwnlib.h"
#include "source/parse.h"
#include "source/print.h"
#include "source/Myaml.h"
*/
#include <pwn.h>
#include <iostream>
#include <string>
using namespace std;
string exec_path;

int main()
{
    //How to use ?
    //Customize functions by writing defaults or defining templates
    //For Example,

    M_Yaml yaml;
    yaml.load_all_files();
    yaml.get_owner_path();
    //cout << yaml.get_execu_path() << endl;
    cout << yaml.get_config_file_path(1) << endl;
    //yaml.load_file_();
    cout << "Input your file << ";
    cin >> exec_path;
    PWN<Auto_Mod> *p = new PWN<Auto_Mod>(exec_path);

    p->analyze_manual_();
    p->gengerate_();

}
