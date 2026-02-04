#include "Graphics/Renderer.hpp"
#include "ImGui/imgui.h"
#include "dependencies/Touch.hpp"
#include <memory>



int main() {
    auto renderer = std::make_unique<Renderer>();
    auto displayInfo = renderer->getDisplayInfo();
    
    if (!renderer->init()) {
        return 1;
    }

    while (true) {
        renderer->beginFrame();
    ImGuiIO &io = ImGui::GetIO();
    static ImVec4 clear_color = ImVec4(0, 0, 0, 0);
    static bool show_demo_window = true;
    static bool show_another_window = false;
    static bool lightmode = false;
    static float f = 0.0f;
    static int counter = 0;
    if (show_demo_window)
       ImGui::ShowDemoWindow(&show_demo_window);
       
        if (ImGui::Begin("Hello world")) {
        ImGui::Text("This is some useful text.");
            ImGui::Checkbox("Demo Window", &show_demo_window);
            ImGui::Checkbox("Another Window", &show_another_window);
            ImGui::Checkbox("Light mode", &lightmode);
        ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
        ImGui::ColorEdit3("clear color", (float *) &clear_color);
        if (ImGui::Button("Button"))
            counter++;
        ImGui::SameLine();
        ImGui::Text("counter = %d", counter);

        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate,
                    io.Framerate);
        ImGui::End();
    }
    if (show_another_window)
    {
        ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
        ImGui::Text("Hello from another window!");
        if (ImGui::Button("Close Me"))
            show_another_window = false;
        ImGui::End();
    }

    if (lightmode) {
        ImGui::StyleColorsLight();
    } else {
        ImGui::StyleColorsDark();
    }



        
        renderer->endFrame();
    }
    
    return 0;
}