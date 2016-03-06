#ifndef _DATA_H_
#define _DATA_H_

#include <string>
#include <vector>
#include <map>

#include "mempack.h"

template<typename T>
class Data
{
public:
    static Data<T> Get(std::string path);
    
    void Free();
    
    T& operator*()
    {
        if(magic_array[index] == magic)
        {
            return data[index];
        }
        else
            return data[0];
    }
    
    T* operator->()
    {
        if(magic_array[index] == magic)
        {
            return &data[index];
        }
        else
            return &data[0];
    }
    
    operator unsigned int() const{ return handle; }
private:
    Data(){}
    Data(unsigned int i, unsigned int m) : index(i), magic(m){}
    
    union
    {
        struct
        {
            unsigned int index:16;
            unsigned int magic:16;
        };
        unsigned int handle;
    };
    
    // Static stuff
    static std::vector<T> data;
    static std::vector<unsigned int> magic_array;
    static std::map<std::string, Data<T>> handles;
};

template<typename T>
std::vector<T> Data<T>::data;
template<typename T>
std::vector<unsigned int> Data<T>::magic_array;
template<typename T>
std::map<std::string, Data<T>> Data<T>::handles;

template<typename T>
Data<T> Data<T>::Get(std::string path)
{
    static unsigned int next_magic = 0;
    Data<T> handle;
    std::map<std::string, Data<T>>::iterator hIt;
    if((hIt = handles.find(path)) != handles.end())
    {
        handle = hIt->second;
    }
    else
    {
        //TODO Load resource from file;
        T resource;
        //
        next_magic++;
        data.push_back(resource);
        magic_array.push_back(next_magic);
        handle = Data<T>(data.size() - 1, next_magic);
    }
    return handle;
}

#endif