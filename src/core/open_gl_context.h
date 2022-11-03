//
// Created by Mateusz Palkowski on 02/11/2022.
//

#ifndef MINECPPRAFT_OPEN_GL_CONTEXT_H
#define MINECPPRAFT_OPEN_GL_CONTEXT_H

#include "GL/glew.h"
#include "GLFW/glfw3.h"

namespace prototype {

class OpenGlContext {
 public:
  OpenGlContext(GLFWwindow* window);
  void Init();
  void SwapBuffers();

 private:
  GLFWwindow* window_;
};

}

#endif  // MINECPPRAFT_OPEN_GL_CONTEXT_H
