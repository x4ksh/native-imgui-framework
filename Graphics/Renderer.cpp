#include "Renderer.hpp"
#include "ImGui/imgui.h"
#include "ImGui/backends/imgui_impl_opengl3.h"
#include "ImGui/backends/imgui_impl_android.h"
#include "dependencies/Touch.hpp"

Renderer::Renderer() {}

Renderer::~Renderer() {
    shutdown();
}

bool Renderer::init() {
    auto displayInfo = android::ANativeWindowCreator::GetDisplayInfo();
    m_width = displayInfo.width;
    m_height = displayInfo.height;
    m_nativeWindow = android::ANativeWindowCreator::Create("AWindow", m_width, m_height, false, false);
    if (!m_nativeWindow) return false;
    ANativeWindow_setBuffersGeometry(m_nativeWindow, m_width, m_height, WINDOW_FORMAT_RGBA_8888);
    m_display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    eglInitialize(m_display, nullptr, nullptr);
    EGLConfig cfg;
    EGLint num;
    EGLint attribs[] = {
        EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
        EGL_RED_SIZE, 8, EGL_GREEN_SIZE, 8, EGL_BLUE_SIZE, 8, EGL_ALPHA_SIZE, 8,
        EGL_DEPTH_SIZE, 0, EGL_STENCIL_SIZE, 0, EGL_NONE
    };
    eglChooseConfig(m_display, attribs, &cfg, 1, &num);
    m_surface = eglCreateWindowSurface(m_display, cfg, m_nativeWindow, nullptr);
    EGLint ctx_attribs[] = {EGL_CONTEXT_CLIENT_VERSION, 3, EGL_NONE};
    m_context = eglCreateContext(m_display, cfg, EGL_NO_CONTEXT, ctx_attribs);
    if (!eglMakeCurrent(m_display, m_surface, m_surface, m_context)) return false;
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.IniFilename = nullptr;
    io.DisplaySize = ImVec2((float)m_width, (float)m_height);
    ImGui_ImplOpenGL3_Init("#version 300 es");
    ImGui_ImplAndroid_Init(m_display, m_surface);
    m_prevTime = std::chrono::steady_clock::now();
    int max_size = (displayInfo.height > displayInfo.width ? displayInfo.height : displayInfo.width);
    int min_size = (displayInfo.height < displayInfo.width ? displayInfo.height : displayInfo.width);
    G_Width = static_cast<float>(max_size);
    G_Height = static_cast<float>(min_size);
    A_X = max_size;
    A_Y = max_size;
    touch::init(max_size, min_size, (uint8_t)displayInfo.orientation);
    
    ImGui::GetStyle().ScaleAllSizes(3.0f);
    
    m_initialized = true;
    return true;
}

void Renderer::beginFrame() {
    auto now = std::chrono::steady_clock::now();
    float delta = std::chrono::duration<float>(now - m_prevTime).count();
    m_prevTime = now;
    ImGuiIO& io = ImGui::GetIO();
    io.DeltaTime = (delta > 0.0f) ? delta : (1.0f / 60.0f);
    io.DisplaySize = ImVec2((float)m_width, (float)m_height);
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplAndroid_NewFrame();
    ImGui::NewFrame();
}

void Renderer::endFrame() {
    glViewport(0, 0, m_width, m_height);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    eglSwapBuffers(m_display, m_surface);
}

void Renderer::shutdown() {
    if (!m_initialized) return;
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplAndroid_Shutdown();
    ImGui::DestroyContext();
    if (m_display != EGL_NO_DISPLAY) {
        eglMakeCurrent(m_display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
        if (m_context != EGL_NO_CONTEXT) eglDestroyContext(m_display, m_context);
        if (m_surface != EGL_NO_SURFACE) eglDestroySurface(m_display, m_surface);
        eglTerminate(m_display);
    }
    m_initialized = false;
}
