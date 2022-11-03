//
// Created by Mateusz Palkowski on 02/11/2022.
//
#include "application.h"

#include <iostream>

#include "core/time.h"

namespace prototype {

Application* Application::s_instance_ = nullptr;

Application::Application(std::unique_ptr<Delegate> delegate)
    : delegate_(std::move(delegate)),
      application_data_(delegate->GetApplicationData()),
      window_(application_data_.title, application_data_.width,
              application_data_.height) {
  s_instance_ = this;
}

int Application::Run() {
  window_.Init();
//  key_source_.Init();
//  mouse_source_.Init();
  ui_.Init();

  delegate_->Init();

  glClearColor(0.1f, 0.1f, 0.1f, 1.0f); // this should be done by renderer

  // TODO: add event bus, listen for window close event

  event_bus_.Subscribe(Event::Type::WindowClosed, [this](Event e){
    std::cout << "Close" << std::endl;
    is_running_ = false;
  });

  while (is_running_) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    float time = Time::GetTime();
    float delta_time = time - last_frame_time_;
    last_frame_time_ = time;

    if (!window_.IsMinimized()) {
      delegate_->OnUpdate(delta_time);

      ui_.Begin();
      delegate_->OnImGuiUpdate();
      ui_.End();
    }

    window_.OnUpdate();
    event_bus_.Dispatch();
  }
  return 0;
}

Window& Application::GetWindow() { return window_; }
prototype::Application& Application::Get() { return *s_instance_; }

}  // namespace prototype
