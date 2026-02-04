LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := ImGui_executable.sh

LOCAL_C_INCLUDES += $(LOCAL_PATH)
LOCAL_C_INCLUDES += $(LOCAL_PATH)/dependencies
LOCAL_C_INCLUDES += $(LOCAL_PATH)/ImGui
LOCAL_C_INCLUDES += $(LOCAL_PATH)/ImGui/backends 

LOCAL_SRC_FILES := main.cpp \
Graphics/Renderer.cpp \
dependencies/Touch.cpp \
ImGui/imgui.cpp \
ImGui/imgui_draw.cpp \
ImGui/imgui_demo.cpp \
ImGui/imgui_widgets.cpp \
ImGui/imgui_tables.cpp \
ImGui/backends/imgui_impl_opengl3.cpp \
ImGui/backends/imgui_impl_android.cpp

LOCAL_LDLIBS := -llog -landroid -lEGL -lGLESv3
LOCAL_CPPFLAGS  := -std=c++17  -fexceptions -frtti -O3

include $(BUILD_EXECUTABLE)