//
// Created by Mateusz Palkowski on 02/11/2022.
//
#include "open_gl_context.h"

#include <iostream>

#include "GL/glew.h"

namespace prototype {

OpenGlContext::OpenGlContext(GLFWwindow* window)
  : window_(window){

}

void OpenGlContext::Init() {
  glfwMakeContextCurrent(window_);
  if (glewInit() != GLEW_OK) {
    std::cout << "No Glew Init" << std::endl;
  }

  std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;

}
void OpenGlContext::SwapBuffers() {
  glfwSwapBuffers(window_);
}
}