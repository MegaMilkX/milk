#ifndef _TYPEID_H_
#define _TYPEID_H_

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
        return id;
    };
};

#endif