#ifndef _R3D_H_
#define _R3D_H_

#include <map>
#include <vector>

#include <stdint.h>

#include "r3dattrib.h"

class R3DData
{
public:
    typedef int type_indexl
    bool Read(File file);
    bool Write(File file);
	
    template<typename T>
    void PushAttribute(R3DAttr* data);
    template<typename T>
    T GetAttribute(int id = 0);
private:
    std::map<type_index, std::vector<R3DAttrib*>> attributes;
};

template<typename T>
void R3DData::PushAttribute(R3DAttr* data)
{
    R3DAttr* new_attr = data.clone();
    attributes.insert(std::make_pair(new_attr->type_index(), new_attr));
}

template<typename T>
T* R3DData::GetAttribute(int id = 0)
{
    std::vector<R3DAttrib*> vec = attributes[T::type_index()];
    
    if(id < vec.size() && id >= 0)
    {
        return (T*)vec[id];
    }
    else
    {
        return 0;
    }
}

#endif
