#ifndef _MACROS_H_
#define _MACROS_H_

#define _DEF_CLASS_BODY(FIELDS) FIELDS

#define DEF_COMPONENT(typename) \
class typename \
{ \
public: \
    static typename* Create(Node* parent); \
    static typename* Create(); \
    _DEF_CLASS_BODY \
#define _DEF_CLASS_BODY(FIELDS) \
    FIELDS \
#undef _DEF_CLASS_BODY \
} 


#endif