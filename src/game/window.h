//
// Created by mateu on 01.11.2022.
//

#ifndef MINECPPRAFT_WINDOW_H
#define MINECPPRAFT_WINDOW_H

#include <memory>

#include "GL/glew.h"
#include "GLFW/glfw3.h"

class Window {
 public:
  Window(std::string title, int width, int height);
  ~Window();

  bool Init();
  void Update();
  bool IsOpen();
  GLFWwindow* GetWindow();
  int GetWidth();
  int GetHeight();

 private:
  GLFWwindow* window_;
  std::string title_;
  int width_, height_;


};

#endif  // MINECPPRAFT_WINDOW_H
