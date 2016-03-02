#ifndef _GFX_H_
#define _GFX_H_

#include <windows.h>
#include "glextutil.h"

#include "gfxcamera.h"
#include "gfxtarget.h"

GFXTarget*  GFXInit(HWND hWnd);
void        GFXRender();
void        GFXCleanup();

#endif