#ifndef _MACRO_READERS_DEF_H_
#define _MACRO_READERS_DEF_H_

#include "macro_typed_expr.h"
#include "macro_for_each_arg.h"
#include "macro_narg.h"

class Reader
{
public:
    virtual std::string Extension() = 0;
    virtual bool Read(File file, void* data);
};

#define READERS(...) \
    int ReaderCount() { return PP_NARGS(__VA_ARGS__); } \
    std::string GetReaderExtension(int id) \
    { \
        std::string ext; \
        switch(id) \
        { \
            FOR_EACH_ARG(CASE, __VA_ARGS__) \
        } \
        return ext; \
    } 
    
#define CASE(i, arg) case i: ext = "STRIP(arg)"; break;

#endif