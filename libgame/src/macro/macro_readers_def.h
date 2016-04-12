#ifndef _MACRO_READERS_DEF_H_
#define _MACRO_READERS_DEF_H_

#include "macro_typed_expr.h"
#include "macro_for_each_arg.h"
#include "macro_narg.h"

class Reader
{
public:
    virtual std::string Extension() = 0;
    virtual bool Read(File file, void* data) = 0;
};

#define READERS(...) \
    static int ReaderCount() { return PP_NARGS(__VA_ARGS__); } \
    static std::string GetReaderExtension(int id) \
    { \
        std::string ext; \
        switch(id) \
        { \
            FOR_EACH_ARG(CASE_EXT, __VA_ARGS__) \
            default: break; \
        } \
        return ext; \
    } \
    bool Read(int id, std::string path) \
    { \
        bool result = false; \
        switch(id) \
        { \
            FOR_EACH_ARG(CASE_READ, __VA_ARGS__) \
            default: result = false; break; \
        } \
        return result; \
    } 
    
#define CASE_EXT(i, arg) case i: ext = "STRIP(arg)"; break;
#define CASE_READ(i, arg) case i: result = TYPEOF(arg)(path, this); break;

#endif