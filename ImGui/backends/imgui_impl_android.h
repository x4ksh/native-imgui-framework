// backends/imgui_impl_android.h
#pragma once
#include <EGL/egl.h>

#ifdef __cplusplus
extern "C" {
#endif

bool ImGui_ImplAndroid_Init(EGLDisplay display, EGLSurface surface);
void ImGui_ImplAndroid_NewFrame(void);
void ImGui_ImplAndroid_Shutdown(void);
bool ImGui_ImplAndroid_HandleInputEvent(void* event);

#ifdef __cplusplus
}
#endif