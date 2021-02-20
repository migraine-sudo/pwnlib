#ifndef __PRINT__
#define __PRINT__

#include <string>
#include <iostream>
#include <vector>
using namespace std;

const int DEFAULT = 0x0;    // 000000
const int F_BLACK = 0x01;   // 000001
const int F_RED = 0x02;     // 000010
const int F_GREEN = 0x03;   // 000011
const int F_YELLOW = 0x04;  // 000100
const int F_BLUE = 0x05;    // 000101
const int F_DPURPLE = 0x06; // 000110
const int F_WHITE = 0x07;   // 000111
const int F_PURPLE = 0x11;

const int B_BLACK = 0x08; // 001000
const int B_RED = 0x10;   // 010000
const int B_GREEN = 0x18; // 011000
const int B_BROWN = 0x80; // 100000
const int B_BLUE = 0x88;  // 101000
const int B_WHITE = 0x90; // 110000

enum PRINT_FORMAT
{
    BLOCK = 0,
    LINEAR
};

//Help C++ developer to print string in a format
//For Example:
//        Print out(str);
//        out.color_(F_GREEN);
//        out.out_format_(BLOCK);
class Print
{
public:
    Print(string str, int color) : print_str(str) {}
    Print(string str) : print_str(str) {}
    Print() {}
    ~Print() {}
    void str_(string str) { print_str = str; }
    void out_()
    {
        out_line_();
        cout << endl;
    }
    void out_(string str)
    {
        out_line_(str);
        cout << endl;
    }
    void out_line_()
    {
        set_color(this->color);
        cout << print_str; 
        set_color(DEFAULT);
    }
    void out_line_(string str)
    {
        this->print_str=str;
        set_color(this->color);
        cout << print_str; 
        set_color(DEFAULT);
    }
    inline void out_format_(PRINT_FORMAT format);
    inline void color_(const int color) { this->color = color; } // F_BLACK F_RED F_GREEN ...

protected:
    inline void set_color(int color);
    inline void _block_print();

private:
    string print_str;
    int color = DEFAULT;
};

inline void Print::out_format_(PRINT_FORMAT format)
{
    switch (format)
    {
    case BLOCK:
        _block_print();
        break;
    case LINEAR:
        break;
    default:
        out_();
        break;
    }
}

inline int max_line(string str)
{
    int pos1{0}, pos2{0}, max_len{0};
    string split = "\n";
    string tmp_str;
    while ((pos2 = str.find(split, pos1)) >= 0)
    {
        tmp_str = str.substr(pos1, pos2 - pos1);
        if (max_len < tmp_str.length())
            max_len = tmp_str.length();
        pos1 = pos2 + 1;
    }
    return max_len;
}

//Print STR in one BLOCK
inline void Print::_block_print()
{
    set_color(this->color);
    int max_len{max_line(print_str)};
    string line(max_len + 2, '-');
    if (print_str.empty())
    {
        set_color(DEFAULT); //reset color
        return;
    }
    cout << line << endl
         << '|';
    for (auto iter = print_str.begin(); iter != print_str.end(); iter++) //Some bugs if using -> for (auto : print_str )
    {
        static int len{1};
        if ((*iter) == '\n' && iter != print_str.end() - 1)
        {
            while (len <= max_len)
            {
                cout << ' ';
                len++;
            }
            cout << '|' << endl
                 << '|';
            len = 0;
        }
        else if (iter == print_str.end() - 1)
        {
            while (len <= max_len)
            {
                cout << ' ';
                len++;
            }
            cout << '|' << endl;
            len = 0;
        }
        else
            cout << (*iter);
        len++;
    }
    cout << line << endl;
    set_color(DEFAULT); //reset color
}

inline void Print::set_color(int color)
{
    switch (color)
    {
    case F_BLACK:
        std::cout << "\033[30m";
        break;
    case F_RED:
        std::cout << "\033[31m";
        break;
    case F_GREEN:
        std::cout << "\033[32m";
        break;
    case F_YELLOW:
        std::cout << "\033[33m";
        break;
    case F_BLUE:
        std::cout << "\033[34m";
        break;
    case F_PURPLE:
        std::cout << "\033[35m";
        break;
    case F_WHITE:
        std::cout << "\033[37m";
        break;

    case B_BLACK:
        std::cout << "\033[40m";
        break;
    case B_RED:
        std::cout << "\033[41m";
        break;
    case B_GREEN:
        std::cout << "\033[42m";
        break;
    case B_BROWN:
        std::cout << "\033[43m";
        break;
    case B_BLUE:
        std::cout << "\033[44m";
        break;
    case B_WHITE:
        std::cout << "\033[47m";
        break;
    default:
        std::cout << "\033[39m";
        std::cout << "\033[49m";
        break;
    }
}
#endif
