//
// Created by Mateusz Palkowski on 30/10/2022.
//

#include "chunk_renderer_naive.h"

#include <array>

#include "config.h"
#include "gl_util.h"

// improvement - use memcpy to populate big vertex array

ChunkRendererNaive::ChunkRendererNaive(glm::vec3 origin) : origin_(origin) {
  std::cout << "Creating " << count_ << " cubes";
  // initialize gl buffers and stuff necessary to draw a chunk
  GL_CALL(glGenVertexArrays(count_, vbo_));
  GL_CALL(glGenBuffers(count_, vb_));
  GL_CALL(glGenBuffers(count_, ib_));
  for (int x = 0; x < size_x_; ++x) {
    for (int y = 0; y < size_y_; ++y) {
      for (int z = 0; z < size_z_; ++z) {
        int i = x * size_z_ * size_y_ + y * size_z_ + z;
        GL_CALL(glBindVertexArray(vbo_[i]));
        GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, vb_[i]));
        float r, g, b, a = 1.0f;
        if (i%3 == 0) {
           r = 1.0f; g = 0.0f; b=0.0f;
        } else if (i%3 == 1) {
          r = 0.0f; g = 1.0f; b=0.0f;
        } else {
          r = 0.0f; g = 0.0f; b=1.0f;
        }

        float x_f = x, y_f = y, z_f = z;
        std::array<float, 56> vertices = {
            x_f, y_f, z_f, r, g, b, a,
            x_f + 1.0f, y_f, z_f, r, g, b, a,
            x_f + 1.0f, y_f + 1.0f, z_f, r, g, b, a,
            x_f, y_f + 1.0f, z_f, r, g, b, a,
            x_f, y_f, z_f + 1.0f, r, g, b, a,
            x_f + 1.0f, y_f, z_f + 1.0f, r, g, b, a,
            x_f + 1.0f, y_f + 1.0f, z_f + 1.0f, r, g, b, a,
            x_f, y_f + 1.0f, z_f + 1.0f, r, g, b, a,
        };

        GL_CALL(glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 56, vertices.data(),
                             GL_STATIC_DRAW));
        GL_CALL(glEnableVertexAttribArray(0));
        GL_CALL(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 7, nullptr));
        GL_CALL(glEnableVertexAttribArray(1));
        GL_CALL(glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 7, (const void*)(sizeof(float) * 3)));

        std::array<unsigned int, 36> indices = {
            0, 1, 2, 2, 3, 0, // front
            1, 5, 6, 6, 3, 1, // right
            5, 4, 7, 7, 6, 5, // back
            4, 0, 3, 3, 7, 4, // left
            3, 2, 6, 6, 7, 3, // top
            4, 5, 1, 1, 0, 4 // bottom
        };
        GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib_[i]));
        GL_CALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * 36, indices.data(), GL_STATIC_DRAW));
      }
    }
  }

  std::string res(RESOURCE_PATH);
  shader_ = gl::CreateShader(res + "shaders/color_cube_vertex.glsl",
                             res + "shaders/color_cube_fragment.glsl");
  GL_CALL(glUseProgram(shader_));

  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LEQUAL);
}

void ChunkRendererNaive::Render(const glm::mat4& mvp) {
  // bind buffers, shaders and draw
  for (int i = 0; i < count_; ++i) {
    GL_CALL(glBindVertexArray(vbo_[i]));
    GL_CALL(glUniformMatrix4fv(glGetUniformLocation(shader_, "u_MVP"), 1,
                               GL_FALSE, &mvp[0][0]));
    int size;
    glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
    GL_CALL(glDrawElements(GL_TRIANGLES, size / sizeof(unsigned int), GL_UNSIGNED_INT, nullptr));
  }
}
