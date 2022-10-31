//
// Created by Mateusz Palkowski on 30/10/2022.
//

#include "game_loop.h"

#include <iostream>

#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "imgui/imgui.h"

namespace {
void WindowSizeCallback(GLFWwindow* window, int width, int height) {
  GameLoop& game_loop =
      *static_cast<GameLoop*>(glfwGetWindowUserPointer(window));
  game_loop.OnWindowResize(width, height);
}

}  // namespace

GameLoop::GameLoop(GLFWwindow* window, int screen_width, int screen_height)
    : screen_width_(screen_width),
      screen_height_(screen_height),
      projection_(glm::perspective(
          glm::radians(45.0f), screen_width_ / screen_height_, 0.1f, 100.0f)),
      chunk_renderer_(glm::vec3(1.0f)),
      key_input_({GLFW_KEY_Q}),
      mouse_input_(window) {
  glfwSetWindowUserPointer(static_cast<GLFWwindow*>(window), this);
  glfwSetWindowSizeCallback(static_cast<GLFWwindow*>(window),
                            &WindowSizeCallback);
}

void GameLoop::Update(float delta_time) {
  UpdateFixedTime(delta_time);
  time_elapsed_ += delta_time;

  camera_.UpdateKeyboard(delta_time);

  if (IsMouseToggleOn()) {
    camera_.UpdateMouse(delta_time);
  }

  mvp_ = projection_ * camera_.GetViewMatrix() * glm::mat4(1.0f);
}

void GameLoop::UpdateFixedTime(float delta_time) {
  float ms_per_update = 0.016f;  // 16 ms per update
  fixed_time_elapsed_ += delta_time;
  if (fixed_time_elapsed_ < ms_per_update) {
    return;
  }
  // UpdateKeyboard with fixed timing

  // end update
  fixed_time_elapsed_ = 0.0f;
}

bool GameLoop::IsMouseToggleOn() {
  bool current_state = key_input_.IsKeyDown(GLFW_KEY_Q);

  if (!last_state_ && current_state) {
    toggle_state_ = !toggle_state_;
  }

  mouse_input_.CaptureMouse(toggle_state_);

  last_state_ = current_state;
  return toggle_state_;
}

void GameLoop::Render() { chunk_renderer_.Render(mvp_); }

bool GameLoop::ShouldRenderUI() { return true; }
void GameLoop::RenderUI() {
  auto params = camera_.GetCameraParams();

  ImGui::Text("Press Q to toggle camera mouse movement");
  ImGui::Text("Camera controls: %s", toggle_state_ ? "on" : "off");
  ImGui::SliderFloat("Mouse sensitivity", &params.Sensitivity, 0.0f, 0.3f);
  ImGui::SliderFloat("Camera speed", &params.Speed, 0.0f, 10.0f);
  ImGui::Text("%.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate,
              ImGui::GetIO().Framerate);
  ImGui::Text("Camera pos (%.1f, %.1f, %.1f)", params.Position.x,
              params.Position.y, params.Position.z);
}


void GameLoop::OnWindowResize(int width, int height) {
  screen_width_ = width;
  screen_height_ = height;
  projection_ = glm::perspective(glm::radians(45.0f),
                                 screen_width_ / screen_height_, 0.1f, 100.0f);
}
