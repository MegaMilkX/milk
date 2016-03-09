#ifndef _VERTEX_ATTRIB_H_
#define _VERTEX_ATTRIB_H_

#include "typeid.h"
#include "math3f.h"

#define DEF_VERTEX_ATTR(name, type, count)\
struct name: VertexAttr<count, type>\
{name(type& v):VertexAttr(v){}}

template<short count, class T>
struct VertexAttr
{
    T value;
    static short elemCount() { return count; };
    static int elemType(){ return TypeInfo<float>::GetId(); }
    static size_t size(){ return sizeof(T); }
    
protected:
    VertexAttr(T _value)
        : value(_value) {};
};

DEF_VERTEX_ATTR(AttrPosition, vec3f, 3);
DEF_VERTEX_ATTR(AttrNormal, vec3f, 3);
DEF_VERTEX_ATTR(AttrUV, vec2f, 2);
DEF_VERTEX_ATTR(AttrRGBA, vec4f, 4);

#endif