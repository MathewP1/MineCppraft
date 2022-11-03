//
// Created by Mateusz Palkowski on 02/11/2022.
//

#include "ui.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include "core/application.h"

namespace prototype {

void UI::Init() {
  ImGui::CreateContext();
  auto* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetWindowHandle());
  ImGui_ImplGlfw_InitForOpenGL(window, true);
  const char* glsl_version = "#version 410";  // should match OpenGL 4.1
  ImGui_ImplOpenGL3_Init(glsl_version);
  ImGui::StyleColorsDark();
}
void UI::Begin() {
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();
}
void UI::End() {
//  ImGuiIO& io = ImGui::GetIO();
//  Application& app = Application::Get();
//  io.DisplaySize = ImVec2((float)app.GetWindow().GetWidth(), (float)app.GetWindow().GetHeight());

  // Render
  ImGui::Render();
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

UI::~UI() {
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();
}

}  // namespace prototype