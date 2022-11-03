//
// Created by Mateusz Palkowski on 02/11/2022.
//
#include "window.h"

#include <iostream>

#include "core/event.h"
#include "core/event_bus.h"
#include "core/key_source.h"

namespace prototype {
Window::Window(const std::string& title, int width, int height)
 : title_(title), width_(width), height_(height){}

Window::~Window() {
  if (is_initialized_) {
    glfwDestroyWindow(window_);
    window_ = nullptr;
    glfwTerminate();
  }
}

void Window::SetVSync(bool vsync) {
  if (vsync) {
    glfwSwapInterval(1);
  } else {
    glfwSwapInterval(0);
  }
  is_vsync_ = vsync;
}
bool Window::IsVSync() { return is_vsync_; }

void Window::Init() {
  if (is_initialized_) {
    std::cout << "already initialized!" << std::endl;
    return;
  }
  glfwInit();  // TODO: runtime error if failed

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  window_ = glfwCreateWindow(width_, height_, title_.c_str(), NULL, NULL);
  open_gl_context_.emplace(window_);
  open_gl_context_->Init();

  SetVSync(true);

  glfwSetWindowUserPointer(window_, this);
  glfwSetWindowSizeCallback(window_, [](GLFWwindow* window, int width, int height) {
    auto win = *static_cast<Window*>(glfwGetWindowUserPointer(window));
    win.width_ = width;
    win.height_ = height;
    Event e {
        .window_resize {width, height},
        .type = Event::Type::WindowResized
    };
    EventBus::Get().Publish(e);
  });

  glfwSetWindowCloseCallback(window_, [](GLFWwindow* window) {
    Event e {
      .type = Event::Type::WindowClosed
    };
    EventBus::Get().Publish(e);
  });

  glfwSetKeyCallback(window_, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_Q) {
      Event e;
      if (action == GLFW_PRESS) {
        e = Event{
          .key_pressed = KeyCode::Q,
          .type = Event::Type::KeyPressed
        };
      } else if (action == GLFW_RELEASE) {
        e = Event{
          .key_released = KeyCode::Q,
          .type = Event::Type::KeyReleased
        };
      }
      EventBus::Get().Publish(e);
    }
    KeySource::Get().OnGLFWKey(key, scancode, action, mods);
  });
  is_initialized_ = true;
}

bool Window::IsMinimized() { return is_minimized_; }
void Window::OnUpdate() {
  glfwPollEvents();
  open_gl_context_->SwapBuffers();
}
int Window::GetWidth() { return width_; }

int Window::GetHeight() { return height_; }

GLFWwindow* Window::GetWindowHandle() { return window_; }
}  // namespace prototype
