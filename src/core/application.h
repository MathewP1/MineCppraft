//
// Created by Mateusz Palkowski on 02/11/2022.
//

#ifndef MINECPPRAFT_CORE_APPLICATION_H
#define MINECPPRAFT_CORE_APPLICATION_H

#include <string>

#include "core/event_bus.h"
#include "core/key_source.h"
#include "core/ui.h"
#include "core/window.h"

namespace prototype {

struct ApplicationData {
  std::string title;
  int width;
  int height;
  // add stuff like cmdline args, working directory etc...
};

class Application {
 public:
  class Delegate {
   public:
    virtual ~Delegate() = default;
    virtual ApplicationData GetApplicationData() = 0;
    virtual void Init() = 0;
    virtual void OnUpdate(float delta_time) = 0;
    virtual void OnImGuiUpdate() = 0;
  };

  explicit Application(std::unique_ptr<Delegate> delegate);
  int Run();  // returns exit code

  Window& GetWindow();
  static Application& Get();

 private:
  static Application* s_instance_;
  ApplicationData application_data_;

  bool is_running_ = true;
  float last_frame_time_ = 0.0f;

  std::unique_ptr<Delegate> delegate_;
  Window window_;
  EventBus event_bus_;
//  MouseSource mouse_source_;
  KeySource key_source_;
  UI ui_;
};
}  // namespace prototype

#endif  // MINECPPRAFT_CORE_APPLICATION_H
