#ifndef __NODE__
#define __NODE__
#include<map>
enum OPERATE {MALLOC=0,FREE,WRITE,READ,SHOW};

template<typename T>
class Node
{
public:

private:
    std::map<OPERATE,T> node_map;
    
};

#endif
