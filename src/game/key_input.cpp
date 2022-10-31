//
// Created by Mateusz Palkowski on 31/10/2022.
//
#include "key_input.h"

// initialize static variable
std::vector<KeyInput*> KeyInput::instances_;

KeyInput::KeyInput(std::vector<int> keys) {
  for (int key : keys) {
    keys_[key] = false;
  }
  instances_.push_back(this);
}
KeyInput::~KeyInput() {
  instances_.erase(std::remove(instances_.begin(), instances_.end(), this), instances_.end());
}
bool KeyInput::IsKeyDown(int key) {
  bool result = false;
  if (is_enabled_) {
    auto found = keys_.find(key);
    if (found != keys_.end()) {
      result = keys_[key];
    }
  }
  return result;
}

void KeyInput::Init(GLFWwindow *window) {
  glfwSetKeyCallback(window, KeyInput::OnKeyboardCallback);
}
void KeyInput::OnKeyboardCallback(GLFWwindow *window, int key, int scancode,
                                  int action, int mods) {
  for (auto key_input : instances_) {
    key_input->SetIsKeyDown(key, action != GLFW_RELEASE);
  }
}
void KeyInput::SetIsKeyDown(int key, bool is_down) {
  auto found = keys_.find(key);
  if (found != keys_.end()) {
    found->second = is_down;
  }
}
