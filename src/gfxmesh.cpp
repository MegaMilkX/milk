#include "gfxmesh.h"

//GL_HALF_FLOAT, GL_FIXED, GL_INT_2_10_10_10_REV, GL_UNSIGNED_INT_2_10_10_10_REV and GL_UNSIGNED_INT_10F_11F_11F_REV

std::map<int, int> type_to_gltype = 
{ { TypeInfo<char>::GetId(), GL_BYTE },
  { TypeInfo<unsigned char>::GetId(), GL_UNSIGNED_BYTE },
  { TypeInfo<short>::GetId(), GL_SHORT },
  { TypeInfo<unsigned short>::GetId(), GL_UNSIGNED_SHORT }, 
  { TypeInfo<int>::GetId(), GL_INT }, 
  { TypeInfo<unsigned int>::GetId(), GL_UNSIGNED_INT },
  { TypeInfo<float>::GetId(), GL_FLOAT },
  { TypeInfo<double>::GetId(), GL_DOUBLE } };
  
