//
// Created by mateu on 01.11.2022.
//
#include "window.h"

#include <iostream>

#include "GL/glew.h"
#include "GLFW/glfw3.h"


Window::Window(const std::string& title, int width, int height)
    : title_(title), width_(width), height_(height) {}

Window::~Window() {
  glfwTerminate();
}

bool Window::Init() {
  if (!glfwInit()) return -1;

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  // Set to core profile - necessary on MacOS
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  window_ = glfwCreateWindow(width_, height_, "Hello World", NULL, NULL);
  if (!window_) {
    std::cout << "No Window created" << std::endl;
    return false;
  }

  glfwMakeContextCurrent(window_);
  glfwSwapInterval(0);

  if (glewInit() != GLEW_OK) {
    std::cout << "No Glew Init" << std::endl;
    return false;
  }

  return true;
}

void Window::Update() {
  glfwSwapBuffers(window_);
  glfwPollEvents();
}

bool Window::IsOpen() { return !glfwWindowShouldClose(window_); }

GLFWwindow *Window::GetWindow() { return window_; }
int Window::GetWidth() { return width_; }
int Window::GetHeight() { return height_; }
