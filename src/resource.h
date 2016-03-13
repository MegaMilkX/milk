#ifndef _RESOURCE_H_
#define _RESOURCE_H_

#include <string>
#include <vector>
#include <map>

template<typename T>
class Resource
{
public:
    static Resource<T> Get(std::string name);
    static Resource<T> Create(std::string name);
    static void Free(std::string name);
    static void FreeAll();
    
    T* operator->();
private:
    Resource(){}
    Resource(unsigned int i, unsigned int m) : index(i), magic(m){}
    static bool ResourceExists(std::string name)
    { return handles.find(name) != handles.end(); }

    union
    {
        struct
        {
            unsigned int index:16;
            unsigned int magic:16;
        };
        unsigned int handle;
    };
    
    static std::vector<T> data;
    static std::vector<unsigned int> magic_array;
    static unsigned int next_magic;
    static std::map<std::string, Resource<T>> handles;
    
    class AutoUnloader
    { public: ~AutoUnloader(){ Resource<T>::FreeAll(); } };
    static AutoUnloader unloader;
};

template<typename T>
std::vector<T> Resource<T>::data;
template<typename T>
std::vector<unsigned int> Resource<T>::magic_array;
template<typename T>
unsigned int Resource<T>::next_magic = 0;
template<typename T>
std::map<std::string, Resource<T>> Resource<T>::handles;
template<typename T>
typename Resource<T>::AutoUnloader Resource<T>::unloader;

template<typename T>
Resource<T> Resource<T>::Get(std::string name)
{
    if(ResourceExists(name))
    {
        return handles[name];
    }
    else
    {
        File file = File::Open(name, File::READ);
        T value = ResourceFactory::Create<T>(file);
        
        data.push_back(value);
        next_magic++;
        Resource<T> resource = Resource<T>(data.size() - 1, next_magic);
        handles.insert(std::make_pair(name, resource);
        return resource;
    }
}

template<typename T>
Resource<T> Resource<T>::Create(std::string name)
{
    if(ResourceExists(name))
    {
        return Resource<T>(0, 0);
    }
    else
    {
        T value;
        data.push_back(value);
        next_magic++;
        Resource<T> resource = Resource<T>(data.size() - 1, next_magic);
        handles.insert(std::make_pair(name, resource);
        return resource;
    }
}

template<typename T>
void Resource<T>::Free(std::string name)
{
    if(ResourceExists(name))
    {
        data.erase(handles[name].index);
        magic_array.erase(handles[name].index);
        handles.erase(name);
    }
}

template<typename T>
void Resource<T>::FreeAll()
{
    
}

template<typename T>
T* Resource<T>::operator->()
{
    
}

#endif
