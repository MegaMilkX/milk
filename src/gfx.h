#ifndef _GFX_H_
#define _GFX_H_

#include <windows.h>
#include "glextutil.h"

bool GFXInit(HWND hWnd);
void GFXRender();
void GFXCleanup();

#endif