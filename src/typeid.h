#ifndef _TYPEID_H_
#define _TYPEID_H_

#include <iostream>

static int _NewId()
{
    static int id;
    return ++id;
}

template<typename T>
struct TypeInfo
{
    static int GetId()
    {
        static const int id = _NewId();
        std::cout << id << "\n";
        return id;
    };
};

#endif