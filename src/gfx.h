#ifndef _GFX_H_
#define _GFX_H_

#include <windows.h>
#include "glextutil.h"

#include "gfxshader.h"
#include "gfxmesh.h"
#include "gfxtarget.h"

GFXTarget*  GFXInit(HWND hWnd);
void        GFXCleanup();

void        GFXSwapBuffers();

int         GFXVersion();

#endif