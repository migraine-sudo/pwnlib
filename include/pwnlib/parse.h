#ifndef __PARSE__
#define __PARSE__

#define NODE_MAX_NUM 10

#include "node.h"
#include "print.h"
#include "Mstring.h"
#include <string>
#include <vector>
#include <unistd.h>

/*
 * LIST : Auto_Mod(develping)  Half_Auto_Mod
*/

//Parse_Mod is a class to help class PWN to analyze the Executable file
//You need to overide the virtual functions such as recv_(),send_()..
//to provide the basic funciton of analysing.
class Parse_Mod
{
public:
    Parse_Mod() {
        string cmd[6] = {"help", "h", "quit", "q", "finish", "f"};
        command = vector<string>(cmd, cmd + sizeof(cmd) / sizeof(string));
    }
    bool if_loaded_() const { return if_loaded; } // You can see this function is called by related code in pwnlib
    bool if_abort_() const { return if_abort; }   // You can see this function is called by related code in pwnlib
    vector<string> seed_() const { return seed; } // the seed to help analyse
    int get_round_() const { return round; }      // the analyse round

    void load_node_list_(Node<string> *list){ node_list = list; } //load the node list into analyse program
    void insert_node_list_(string y);             // insert the input data into node_list 
    void show_node_list_();                       // show the result data of analyse in map (dictionary)

    string &menu_buf_() { return menu_buf; }    // store the string of menu
    bool load_(bool load) { if_loaded = load; } // make the programload or reload
    void abort_() { if_abort = true; }          // abort the analyse program

    virtual string recv_(string str){}; // Process the received data
    virtual string send_(int i){};      // Process the data to be sent

protected:
    Node<string> *node_list; // Store the result of analyse for Script Generation
    string menu_buf;
    vector<string> seed;
    int round{0};     // Store the round of program
    string last_data; // Store the lastest data we put into
    vector<string> command;
private:
    bool if_loaded{false};
    bool if_abort{false};
};


inline void Parse_Mod::insert_node_list_(string y)
{
    if (!mstr::in<string>(this->command, y) && !(this->last_data.empty()))
    {
        this->node_list[this->round].insert(this->last_data, y);
    }
}

inline void Parse_Mod::show_node_list_()
{
    int i{0};
    Print out;
    out.str_("Results after analysis");
    out.out_();
    while (i <= this->round)
    {
        out.out_("Round " + to_string(i + 1) + " : ");
        for (auto iter : node_list[i].node_map_())
        {
            //cout << iter.first << iter.second << endl;
            out.str_(iter.first);
            out.out_format_(BLOCK);
            out.str_(string("\t|\n\t-->") + iter.second);
            out.out_();
        }
        i++;
    }
}


/////////////////////////////////////////////
/*               Auto Mod                  */
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

    inline string recv_(string str);
    inline string send_(int i);
};


//override the recv_ to make same judge to help auto analysing.
//Here I judge whether a round of operation is completed by
//judging whether the program outputs menu information
inline string Auto_Mod::recv_(string str)
{
    //cout << "line of " <<str  << " = "<<line_of_string(str) << endl;
    //if (menu_buf_() == str) // Judge if the program has been run for one round.
    
    if(mstr::Traverse_string(menu_buf_(),str)) //Use Traverse_string to  Determine the similarity of two strings
    {
        this->load_(false);
        this->round++;
        menu_buf_() = string("raw");
        sleep(1);
    }
    this->last_data = str;
    return str;
}

inline string Auto_Mod::send_(int i)
{
    insert_node_list_(seed[i]);  // insert seed[i] and this->last_data
    if (i < seed.size())
        return seed[i];
    else
        abort_();
}

/////////////////////////////////////////////
/*            Half Auto Mod                */

class Half_Auto_Mod : public Parse_Mod
{
public:
    Half_Auto_Mod()
    {
#ifndef __DEBUG__
        Print warn;
        warn.color_(B_RED);
        warn.out_("Please Compile with -D__DEBUG__");
#endif

        Print out;
        out.color_(DEFAULT);
        out.out_("Welcome to PwnLib.Working under [ Half Auto Mod ]");
        out.out_("[*]pwnlib shell initializing , using  \"help\" to show more args");
    }
    inline string recv_(string str);
    inline string send_(int i);
};

inline string Half_Auto_Mod::recv_(string str)
{
    if (mstr::Traverse_string(menu_buf_(),str)) //Non-mandatory judgment, give opinions
    {
        cout << "AI:Maybe you should input : finish or quit" << endl;
        menu_buf_() = string("raw");
    }
    this->last_data = str;
    return str;
}

inline string Half_Auto_Mod::send_(int i)
{
    string cmd;
    Print out("[pwnlib] << ");
    out.color_(F_BLUE);
    out.out_line_();
    cin >> cmd;
    while (mstr::in<string>(command, cmd))
    {
        if (cmd == string("help") || cmd == string("h"))
            out.out_("DATA:\ndata such as 1 ,a ,A \nCommand: \n\"help\",\"h\" : \t\t print help list \n\"quit\",\"q\" : \t\t quit the program \n\"finish \",\"f\" : \t Tell our analyse program , one round finish ");
        if (cmd == string("quit") || cmd == string("q"))
        {
            abort_();
            break;
        }
        if (cmd == string("finish") || cmd == string("f"))
        {
            this->load_(false);
            this->round++;
            sleep(1);
            break;
        }
        out.out_line_("[pwnlib] << ");
        cin >> cmd;
    }
    insert_node_list_(cmd);   
    return cmd; 
}

#endif
