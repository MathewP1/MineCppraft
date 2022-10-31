//
// Created by Mateusz Palkowski on 31/10/2022.
//

#ifndef MINECPPRAFT_MOUSE_INPUT_H
#define MINECPPRAFT_MOUSE_INPUT_H

#include "GLFW/glfw3.h"

class MouseInput {
 public:
  MouseInput(GLFWwindow* window);

  void CaptureMouse(bool enable);

 private:
  GLFWwindow* window_;
  bool mouse_captured_ = true;
};

#endif  // MINECPPRAFT_MOUSE_INPUT_H
