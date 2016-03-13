#ifndef _DATAHANDLE_H_
#define _DATAHANDLE_H_

#include <vector>
#include <string>

template<typename DATA>
class Data
{
public:
    Data() : handle(0){}
    DATA* operator->();
    void Release();

    static Data<DATA> Create();
    static Data<DATA> Create(DATA value);
private:
    Data(unsigned int index) : index(index), magic(++Data<DATA>::magic_next){}
    union
    {
        struct
        {
            unsigned int index : 16;
            unsigned int magic : 16;
        };
        unsigned int handle;
    };

    //
    static std::vector<DATA> data_storage;
    static std::vector<unsigned int> magic_storage;
    static std::vector<unsigned int> free_storage;
    static unsigned int magic_next;
};

template<typename DATA>
std::vector<DATA> Data<DATA>::data_storage;
template<typename DATA>
std::vector<unsigned int> Data<DATA>::magic_storage;
template<typename DATA>
std::vector<unsigned int> Data<DATA>::free_storage;
template<typename DATA>
unsigned int Data<DATA>::magic_next = 0;

template<typename DATA>
DATA* Data<DATA>::operator->()
{
    if (magic_storage[index] != magic)
        return 0;
    return &(data_storage[index]);
}

template<typename DATA>
void Data<DATA>::Release()
{
    if (magic == 0)
        return;
    if (Data<DATA>::magic_storage[index] != magic)
        return;
    Data<DATA>::magic_storage[index] = 0;
    Data<DATA>::free_storage.push_back(index);
    Data<DATA>::data_storage[index] = DATA();
}

template<typename DATA>
Data<DATA> Data<DATA>::Create()
{
    Data<DATA> resource;
    unsigned int index;
    if (free_storage.empty())
    {
        index = data_storage.size();
        data_storage.push_back(DATA());
        resource = Data<DATA>(index);
        magic_storage.push_back(resource.magic);
    }
    else
    {
        index = free_storage.back();
        free_storage.pop_back();
        resource = Data<DATA>(index);
        magic_storage[index] = resource.magic;
    }

    return resource;
}

template<typename DATA>
Data<DATA> Data<DATA>::Create(DATA value)
{
    Data<DATA> resource;
    unsigned int index;
    if (free_storage.empty())
    {
        index = data_storage.size();
        data_storage.push_back(value);
        resource = Data<DATA>(index);
        magic_storage.push_back(resource.magic);
    }
    else
    {
        index = free_storage.back();
        free_storage.pop_back();
        resource = Data<DATA>(index);
        data_storage[index] = value;
        magic_storage[index] = resource.magic;
    }

    return resource;
}

#endif