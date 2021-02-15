#ifndef __PARSE__
#define __PARSE__

#include "node.h"
#include "print.h"
#include <string>
#include <vector>

/*
 * LIST : Auto_Mod(develping)  Half_Auto_Mod
*/

//Parse_Mod is a class to help class PWN to analyze the Executable file
//You need to overide the virtual functions such as recv_(),send_()..
//to provide the basic funciton of analysing.
class Parse_Mod
{
public:
    Parse_Mod() {}
    bool if_loaded_() const { return if_loaded; }
    bool if_abort_() const { return if_abort; }
    vector<string> seed_() const { return seed; }

    string &menu_buf_() { return menu_buf; }
    bool load_(bool load) { if_loaded = load; }
    void abort_() { if_abort = true; }

    virtual string recv_(string str){};
    virtual string send_(int i){};

protected:
    string menu_buf;
    vector<string> seed;

private:
    bool if_loaded{false};
    bool if_abort{false};
};

//This Mode Use the "output menu" string to determine whether the program has been run for
//one round, and try to realize a fully automatic program analysis module.
class Auto_Mod : public Parse_Mod
{
public:
    Auto_Mod()
    {
        string array[5] = {"1", "2", "3", "4", "5"};
        seed = vector<string>(array, array + 4);
    }
    //override the recv_ to make same judge to help auto analysing.
    inline string recv_(string str)
    {
        if (menu_buf_() == str) // Judge if the program has been run for one round.
        {
            this->load_(false);
            menu_buf_() = string("raw");
            //cout << "Same!!!" << endl;
            sleep(1);
        }
        return str;
    }
    inline string send_(int i)
    {
        if (i < seed.size())
            return seed[i];
        else
            abort_();
    }
};

#endif
