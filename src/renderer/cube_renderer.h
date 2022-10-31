//
// Created by Mateusz Palkowski on 30/10/2022.
//

#ifndef MINECPPRAFT_CUBE_RENDERER_H
#define MINECPPRAFT_CUBE_RENDERER_H

#include "glm/glm.hpp"

class CubeRenderer {
 public:
  CubeRenderer();
  void Render(const glm::mat4& mvp);
 private:
  unsigned int vbo_{0}, vb_{0}, ib_{0}, shader_{0};
};

#endif  // MINECPPRAFT_CUBE_RENDERER_H
