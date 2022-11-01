

#include "game/window.h"
#include "game/game.h"
#include "game/ui.h"

int main() {
  Window window("OpenGL learning", 1200, 800);
  if (!window.Init()) {
    return 1;
  }

  Ui ui;
  ui.Init(window.GetWindow());
  Game game(window.GetWindow(), window.GetWidth(), window.GetHeight());

  KeyInput::Init(window.GetWindow());

  float delta_time, last_frame, current_frame;
  while (window.IsOpen()) {
    current_frame = glfwGetTime();
    delta_time = current_frame - last_frame;
    last_frame = current_frame;

    game.Clear();

    ui.StartLoop();

    game.Update(delta_time);
    game.Render();
    if (game.ShouldRenderUI()) {
      ui.StartRenderUi();
      game.RenderUI();
      ui.EndRenderUi();
    }

    ui.EndLoop();
    window.Update();
  }

  return 0;
}