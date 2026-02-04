#include "imgui.h"
#include "ANativeWindowCreator.h"
#include <EGL/egl.h>
using namespace android;
extern "C" {
bool ImGui_ImplAndroid_Init(EGLDisplay display, EGLSurface surface) {
    (void)display; (void)surface;
    ImGuiIO& io = ImGui::GetIO();
    io.BackendPlatformName = "LithiumImGui";
    auto info = ANativeWindowCreator::GetDisplayInfo();
    io.DisplaySize = ImVec2((float)info.width, (float)info.height);
    io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);
    return true;
}
void ImGui_ImplAndroid_NewFrame() {}
void ImGui_ImplAndroid_Shutdown() {}
bool ImGui_ImplAndroid_HandleInputEvent(void* event) { (void)event; return false; }
}