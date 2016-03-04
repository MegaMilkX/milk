#ifndef _DATA_H_
#define _DATA_H_

#include <string>

template<typename T>
class Data
{
public:
    static Data<T> Get(std::string path);
    
    void Set(std::string path);
private:
    Data(){}
};

template<typename T>
Data<T> Data<T>::Get(std::string path)
{
#pragma message("Data: Type loading not supported")
    return Data<T>();
}

#endif