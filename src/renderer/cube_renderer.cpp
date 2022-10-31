//
// Created by Mateusz Palkowski on 30/10/2022.
//

#include "cube_renderer.h"

#include "gl_util.h"

#include "config.h"

CubeRenderer::CubeRenderer() {
  // clang-format off
  float vertices[] = {
    -1.0f, -1.0f, 1.0f,
    1.0f, -1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f,
    -1.0f, -1.0f, -1.0f,
    1.0f, -1.0f, -1.0f,
    1.0f, 1.0f, -1.0f,
    -1.0f, 1.0f, -1.0f,
  };

  unsigned int indices[] = {
  0, 1, 2, 2, 3, 0, // front
  1, 5, 6, 6, 3, 1, // right
  5, 4, 7, 7, 6, 5, // back
  4, 0, 3, 3, 7, 4, // left
  3, 2, 6, 6, 7, 3, // top
  4, 5, 1, 1, 0, 4 // bottom
  };
  // clang-format on

  // Create and bind vertex buffer object
  GL_CALL(glGenVertexArrays(1, &vbo_));
  GL_CALL(glBindVertexArray(vbo_));

  GL_CALL(glGenBuffers(1, &vb_));
  GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, vb_));
  GL_CALL(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices,
                       GL_STATIC_DRAW));

  GL_CALL(glEnableVertexAttribArray(0));
  GL_CALL(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),
                                nullptr));

  GL_CALL(glGenBuffers(1, &ib_));
  GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib_));
  GL_CALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
                       GL_STATIC_DRAW));

  std::string res(RESOURCE_PATH);
  shader_ = gl::CreateShader(res + "shaders/basic_vertex.glsl",
                             res + "shaders/basic_fragment.glsl");
  GL_CALL(glUseProgram(shader_));
}

void CubeRenderer::Render(const glm::mat4& mvp) {
  GL_CALL(glBindVertexArray(vbo_));
  GL_CALL(glUseProgram(shader_));

  // pass MVP matrix
  GL_CALL(glUniformMatrix4fv(glGetUniformLocation(shader_, "u_MVP"), 1,
                             GL_FALSE, &mvp[0][0]));

  int size;
  glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
  GL_CALL(glDrawElements(GL_TRIANGLES, size / sizeof(unsigned int),
                         GL_UNSIGNED_INT, nullptr));
}
