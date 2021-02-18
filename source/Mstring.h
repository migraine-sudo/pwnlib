#ifndef __M_STRING__
#define __M_STRING__

#include <algorithm>
namespace mstr{

template <class T>
inline bool in(vector<T> pattern, T str);
inline int line_of_string(string str);
inline bool Traverse_string(string str1 ,string str2);
inline string select_line(string str,int x);

//Check if str can be found in a pattern
template <class T>
inline bool in(vector<T> pattern, T str)
{
    for (auto iter : pattern)
    {
        if (str == iter)
            return true;
    }
    return false;
}

//Determine the similarity of two strings
inline bool Traverse_string(string str1 ,string str2)
{
    int count {0}, i{0};
    int line1{ line_of_string(str1) };
    int line2{ line_of_string(str2) };
    for(; i < line1 ; i++)
    {
       for(int j {0}; j < line2 ; j++)
       {
            if(select_line(str1,i) == select_line(str2,j))
            {    
                count ++;
                continue;
            }
       }    
    }
    cout << "count =" << count;
    cout << "line =" << std::max(line1,line2);
    if(count >= std::max(line1,line2)/2)
        return true;
    else
        return false;
}
//the line of string (defined by '\n')
inline int line_of_string(string str)
{
    int pos1{0}, pos2{0}, i{0};
    string split = "\n";
    while ((pos2 = str.find(split, pos1)) >= 0)
    {
        str.substr(pos1, pos2 - pos1);
        pos1 = pos2 + 1;
        i++;
    }
    return i;
}

//Select one line of string
inline string select_line(string str,int x)
{
    int pos1{0}, pos2{0}, i{1};
    string split = "\n";
    string tmp_str;
    while ((pos2 = str.find(split, pos1)) >= 0 && i <= x)
    {
        tmp_str = str.substr(pos1, pos2 - pos1);
        pos1 = pos2 + 1;
        i++;
    }
    return tmp_str;
}
    
}

#endif
