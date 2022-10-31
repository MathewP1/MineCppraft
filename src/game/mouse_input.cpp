//
// Created by Mateusz Palkowski on 31/10/2022.
//

#include "mouse_input.h"
MouseInput::MouseInput(GLFWwindow* window) : window_(window) {
  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void MouseInput::CaptureMouse(bool enable) {
  mouse_captured_ = enable;
  if (mouse_captured_) {
    glfwSetInputMode(window_, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
  } else {
    glfwSetInputMode(window_, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
  }

  // TODO: Don't jerk mouse on toggle
}
