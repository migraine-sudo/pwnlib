#ifndef __NODE__
#define __NODE__
#include <map>
#include <string>

using namespace std;

enum OPERATE
{
    MALLOC = 0,
    FREE,
    WRITE,
    READ,
    SHOW
};

template <typename T>
class Node
{
public:
    Node(T x, string y)
    {
        node_map.insert(pair<T, string>(x, y));
    }
    Node() {}
    inline void insert(T x, string y);
    //void generate() {}
    std::map<T, string> &node_map_() { return node_map; }

private:
    std::map<T, string> node_map;
};

template <typename T>
inline void Node<T>::insert(T x, string y)
{
    node_map.insert(pair<T, string>(x, y));
}
#endif
