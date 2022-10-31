//
// Created by Mateusz Palkowski on 31/10/2022.
//

#ifndef MINECPPRAFT_KEY_INPUT_H
#define MINECPPRAFT_KEY_INPUT_H

#include <map>
#include <memory>
#include <vector>

#include "GLFW/glfw3.h"

// ripped from stackoverflow
// https://stackoverflow.com/questions/55573238/how-do-i-do-a-proper-input-class-in-glfw-for-a-game-engine

class KeyInput {
 public:
  KeyInput(std::vector<int> keys);
  ~KeyInput();
  bool IsKeyDown(int key);

  static void Init(GLFWwindow* window);

 private:
  bool is_enabled_ = true;
  std::map<int, bool> keys_;
  void SetIsKeyDown(int key, bool is_down);

  static void OnKeyboardCallback(GLFWwindow* window, int key, int scancode,
                                 int action, int mods);
  static std::vector<KeyInput*> instances_;
};

#endif  // MINECPPRAFT_KEY_INPUT_H
