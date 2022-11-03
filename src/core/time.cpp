//
// Created by Mateusz Palkowski on 02/11/2022.
//
#include "time.h"

#include "GLFW/glfw3.h"

namespace prototype {
float Time::GetTime() { return glfwGetTime(); }
}  // namespace prototype