//
// Created by Mateusz Palkowski on 30/10/2022.
//

#include "camera.h"

#include <array>
#include <iostream>

#include "GLFW/glfw3.h"

namespace {
constexpr std::array<int, 7> kKeys = {GLFW_KEY_W, GLFW_KEY_A, GLFW_KEY_S,
                                      GLFW_KEY_D, GLFW_KEY_LEFT_SHIFT, GLFW_KEY_LEFT_CONTROL};

}  // namespace

// void Camera::OnMouseMove(double mouse_delta_x, double mouse_delta_y,
//                          float delta_time) {
//   mouse_delta_x *= mouse_sensitivity_;
//   mouse_delta_y *= mouse_sensitivity_;
//
//   pitch_ = glm::clamp(pitch_ + mouse_delta_y, -90.0, 90.0);
//   yaw_ = glm::mod(yaw_ + mouse_delta_x, 360.0);
//
//   glm::vec3 direction;
//   direction.x = cos(glm::radians(yaw_)) * cos(glm::radians(pitch_));
//   direction.y = sin(glm::radians(pitch_));
//   direction.z = sin(glm::radians(yaw_)) * cos(glm::radians(pitch_));
//   front_ = glm::normalize(direction);
//   view_ = glm::lookAt(position_, position_ + front_, up_);
// }
// void Camera::OnKeyboard(PressedKeys& pk, float delta_time) {
//   float speed = speed_ * delta_time;
//   if (pk.Forward) {
//     position_ += speed * front_;
//   }
//   if (pk.Back) {
//     position_ -= speed * front_;
//   }
//   if (pk.Left) {
//     position_ -= speed * glm::normalize(glm::cross(front_, up_));
//   }
//   if (pk.Right) {
//     position_ += speed * glm::normalize(glm::cross(front_, up_));
//   }
//   view_ = glm::lookAt(position_, position_ + front_, up_);
// }

// if (camera_enabled_) {
//   glfwSetInputMode(w, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
// } else {
//   glfwSetInputMode(w, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
// }

Camera::Camera() : key_input_(std::vector(kKeys.begin(), kKeys.end())) {}

void Camera::UpdateKeyboard(float delta_time) {
  float delta_speed = params_.Speed * delta_time;
  if (key_input_.IsKeyDown(GLFW_KEY_W)) {
    params_.Position += delta_speed * params_.Front;
  }
  if (key_input_.IsKeyDown(GLFW_KEY_S)) {
    params_.Position -= delta_speed * params_.Front;
  }
  if (key_input_.IsKeyDown(GLFW_KEY_A)) {
    params_.Position -=
        delta_speed * glm::normalize(glm::cross(params_.Front, params_.Up));
  }
  if (key_input_.IsKeyDown(GLFW_KEY_D)) {
    params_.Position +=
        delta_speed * glm::normalize(glm::cross(params_.Front, params_.Up));
  }
  if (key_input_.IsKeyDown(GLFW_KEY_LEFT_SHIFT)) {
    params_.Position += delta_speed * params_.Up;
  }
  if (key_input_.IsKeyDown(GLFW_KEY_LEFT_CONTROL)) {
    params_.Position -= delta_speed * params_.Up;
  }
  view_ = glm::lookAt(params_.Position, params_.Position + params_.Front, params_.Up);
  // enable disable camera

  // mouse input
}

const glm::mat4& Camera::GetViewMatrix() { return view_; }

const Camera::Params& Camera::GetCameraParams() { return params_; }
void Camera::UpdateMouse(float delta_time) {
}
