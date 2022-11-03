#include <iostream>
#include <memory>

#include "imgui/imgui.h"

#include "core/application.h"
#include "core/event_bus.h"

using namespace prototype;

class Game : public prototype::Application::Delegate {
 public:
  ~Game() override = default;
  void Init() override {
    std::cout << "Init stuff" << std::endl;
    prototype::EventBus::Get().Subscribe(Event::Type::KeyPressed, [this](Event e) {
      toggle_ = true;
    });
    prototype::EventBus::Get().Subscribe(Event::Type::KeyReleased, [this](Event e) {
      toggle_ = false;
    });
  }

  void OnUpdate(float delta_time) override {
//    std::cout << "OnUpdate, dt: " << delta_time << std::endl;
  }

  void OnImGuiUpdate() override {
    ImGui::Begin("Debug UI");
    ImGui::Text("Hello %s", toggle_ ? "on" : "off");
    ImGui::End();
  }

  prototype::ApplicationData GetApplicationData() override { return {"Game", 800, 600}; }

 private:
  bool toggle_ = false;
};

int main() {
  auto game = std::make_unique<Game>();
  prototype::Application app(std::move(game));
  return app.Run();
}