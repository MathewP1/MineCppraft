//
// Created by Mateusz Palkowski on 30/10/2022.
//

#ifndef MINECPPRAFT_GAME_LOOP_H
#define MINECPPRAFT_GAME_LOOP_H

#include <memory>

#include "game/camera.h"
#include "game/mouse_input.h"
#include "renderer/chunk_renderer_naive.h"

// TODO: split GameWindow and GameLoop classes
class GameLoop {
 public:
  GameLoop(GLFWwindow* window, int screen_width, int screen_height);

  void Update(float delta_time);
  void Render();
  bool ShouldRenderUI();
  void RenderUI();

  // event handlers
  void RegisterInputHandler(void* window);
  void OnWindowResize(int width, int height);

 private:
  void UpdateFixedTime(float delta_time);

  bool IsMouseToggleOn();
  bool toggle_state_ = false;
  bool last_state_ = false;

  float screen_width_, screen_height_;

  float time_elapsed_;
  float fixed_time_elapsed_{0.0f};

  glm::mat4 projection_;
  glm::mat4 mvp_{1.0f};
  Camera camera_;
  ChunkRendererNaive chunk_renderer_;

  KeyInput key_input_;
  MouseInput mouse_input_;
};

#endif  // MINECPPRAFT_GAME_LOOP_H
