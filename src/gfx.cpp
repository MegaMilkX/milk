#include "gfx.h"

#include <iostream>

HDC deviceContext;
HGLRC context;

GFXTarget* rootRenderTarget;

GFXTarget* GFXInit(HWND hWnd)
{
    PIXELFORMATDESCRIPTOR pfd;
    memset(&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR));
    pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 32;
    pfd.cDepthBits = 32;
    pfd.iLayerType = PFD_MAIN_PLANE;
    
    deviceContext = GetDC(hWnd);
    
    int pixelFormat = ChoosePixelFormat(deviceContext, &pfd);
    
    if(!pixelFormat)
        return 0;
        
    if(!SetPixelFormat(deviceContext, pixelFormat, &pfd))
        return 0;
    
    HGLRC renderingContext = wglCreateContext(deviceContext);
    wglMakeCurrent(deviceContext, renderingContext);
    
    WGLEXTLoadFunctions();
    if(!wglCreateContextAttribsARB)
        return 0;
    
    int attr[] =
    {
        WGL_CONTEXT_MAJOR_VERSION_ARB, 4,
        WGL_CONTEXT_MINOR_VERSION_ARB, 5,
        WGL_CONTEXT_FLAGS_ARB, 0,
        0
    };
    
    HGLRC renderingContext3plus = wglCreateContextAttribsARB(deviceContext, 0, attr);
    
    if(!renderingContext3plus)
        context = renderingContext;
    else
    {
        context = renderingContext3plus;
        wglMakeCurrent(NULL,NULL);
		wglDeleteContext(renderingContext);
		wglMakeCurrent(deviceContext, context);
    }
    int version[2];
    glGetIntegerv(GL_MAJOR_VERSION, &version[0]);
    glGetIntegerv(GL_MINOR_VERSION, &version[1]);
    
    rootRenderTarget = GFXTarget::Create(); //Default OpenGL framebuffer is 0 and we can't change it
                                                //We don't actually need HWND for this, whatever
    
    std::cout << "OpenGL v" << version[0] << "." << version[1] << " ready.\n";
    
    glClearColor (0.0f, 0.0f, 0.0f, 0.0);
    
    return rootRenderTarget;
}

void GFXRender()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    SwapBuffers(deviceContext);
}

void GFXCleanup()
{
    wglMakeCurrent(NULL, NULL);
    wglDeleteContext(context);
}

GFXTarget* GFXGetRootTarget()
{
    return rootRenderTarget;
}
