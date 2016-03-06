#ifndef _MEMPACK_H_
#define _MEMPACK_H_

template<typename T>
class MemPack
{
public:
    int Create();
    void Delete(int id);
    void Reserve(size_t sz);
private:
    static T* start;
    static size_t sz;
    static size_t nextId;
};

#endif