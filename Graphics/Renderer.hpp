#pragma once

#include <EGL/egl.h>
#include <GLES3/gl32.h>
#include <android/native_window.h>
#include <chrono>
#include "dependencies/ANativeWindowCreator.h"

class Renderer {
public:
    Renderer();
    ~Renderer();
     android::ANativeWindowCreator::DisplayInfo getDisplayInfo() {
     return android::ANativeWindowCreator::GetDisplayInfo();
     }

    bool init();
    void beginFrame();
    void endFrame();
    void shutdown();
    bool isInitialized() const { return m_initialized; }

private:
    bool m_initialized = false;
    EGLConfig m_config;
    EGLDisplay m_display = EGL_NO_DISPLAY;
    EGLSurface m_surface = EGL_NO_SURFACE;
    EGLContext m_context = EGL_NO_CONTEXT;
    ANativeWindow* m_nativeWindow = nullptr;

    std::chrono::steady_clock::time_point m_prevTime;
    float G_Width = 0;
    float G_Height = 0;
    int A_X = 0;
    int A_Y = 0;
    int32_t m_width = 0;
    int32_t m_height = 0;
};
