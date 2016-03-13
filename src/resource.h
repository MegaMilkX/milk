#ifndef _RESOURCE_H_
#define _RESOURCE_H_

#include <string>
#include <map>

#include "datahandle.h"

template<typename T>
class Resource
{
public:
    static Data<T> Create(T data, std::string name);
    static Data<T> Get(std::string name);
    static void Free(Data<T> resource);
private:
    static bool ResourceExists(std::string name){ return resources.find(name) != resources.end(); }
    static std::map<std::string, Data<T>> resources;
};

template<typename T>
std::map<std::string, Data<T>> Resource<T>::resources;

#endif
