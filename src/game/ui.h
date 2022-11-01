//
// Created by mateu on 01.11.2022.
//

#ifndef MINECPPRAFT_UI_H
#define MINECPPRAFT_UI_H

#include "GLFW/glfw3.h"

class Ui {
 public:
  ~Ui();
  void Init(GLFWwindow* window);
  void StartLoop();
  void EndLoop();
  void StartRenderUi();
  void EndRenderUi();
};

#endif  // MINECPPRAFT_UI_H
