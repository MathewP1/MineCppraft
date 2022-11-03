//
// Created by Mateusz Palkowski on 02/11/2022.
//

#ifndef MINECPPRAFT_CORE_WINDOW_H
#define MINECPPRAFT_CORE_WINDOW_H

#include <string>
#include <optional>

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "core/open_gl_context.h"

namespace prototype {
class Window {
 public:
  Window(const std::string& title, int width, int height);
  ~Window();

  void Init();
  void OnUpdate();
  void SetVSync(bool vsync);
  bool IsVSync();

  int GetWidth();
  int GetHeight();

  bool IsMinimized();

  GLFWwindow* GetWindowHandle();
 private:
  std::string title_;
  int width_;
  int height_;
  GLFWwindow* window_;
  std::optional<OpenGlContext> open_gl_context_; // TODO: rename optional to late_init or sth

  bool is_initialized_ = false;
  bool is_minimized_ = false;
  bool is_vsync_ = false;
};
}  // namespace prototype

#endif  // MINECPPRAFT_CORE_WINDOW_H
