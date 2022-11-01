//
// Created by Mateusz Palkowski on 30/10/2022.
//

#ifndef MINECPPRAFT_CHUNK_RENDERER_NAIVE_H
#define MINECPPRAFT_CHUNK_RENDERER_NAIVE_H

#include "glm/glm.hpp"

namespace {
constexpr int kSizeX = 1;
constexpr int kSizeY = 1;
constexpr int kSizeZ = 1;
constexpr int kCount = kSizeZ * kSizeY * kSizeX;
}  // namespace

class ChunkRendererNaive {
 public:
  ChunkRendererNaive(glm::vec3 origin);
  void Render(const glm::mat4& mvp);

 private:
  glm::vec3 origin_;
  int size_x_{kSizeX}, size_y_{kSizeY}, size_z_{kSizeZ}, count_{kCount};
  unsigned char blocks[kCount]{0}; // 0 means no block, 1 means a block

  unsigned int vbo_[kCount]{0}, vb_[kCount]{0}, ib_[kCount]{0}, shader_{0};
};

#endif  // MINECPPRAFT_CHUNK_RENDERER_NAIVE_H
