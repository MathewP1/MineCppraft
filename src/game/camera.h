//
// Created by Mateusz Palkowski on 30/10/2022.
//

#ifndef MINECPPRAFT_CAMERA_H
#define MINECPPRAFT_CAMERA_H

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "game/key_input.h"


class Camera {
 public:
  struct Params {
    float Speed{5.0f};
    float Sensitivity{0.07f};
    float Yaw{-90.0f}, Pitch{0.0f};
    glm::vec3 Position{0.0f, 0.0f, 3.0f};
    glm::vec3 Front{0.0f, 0.0f, -1.0f};
    glm::vec3 Up{0.0f, 1.0f, 0.0f};
  };
  Camera();
  void UpdateKeyboard(float delta_time);
  void UpdateMouse(float delta_time);

  const glm::mat4& GetViewMatrix();
  const Params& GetCameraParams();

 private:
  Params params_;
  glm::mat4 view_{glm::lookAt(params_.Position, params_.Position + params_.Front, params_.Up)};
  KeyInput key_input_;
};

#endif  // MINECPPRAFT_CAMERA_H
