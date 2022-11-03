//
// Created by mateu on 01.11.2022.
//

#ifndef MINECPPRAFT_CORE_EVENT_H
#define MINECPPRAFT_CORE_EVENT_H

#include "keyboard.h"

namespace prototype {
struct Event {
  struct WindowResizeEvent {
    int x, y;
  };

  // some kind of KeySource class that makes this easier to work with?
  // multiple event buses? EventBus<Event::Type::Window>
  // EventBus::Get<Event::Type::Window>(); // handles window type events
  // EventBus::Get<Event::Type::Key>(); // handles key type events
  struct KeyEvent {
    KeyCode key_code;
  };

  struct KeyPressedEvent {
    KeyCode key_code;
  };

  struct KeyReleasedEvent {
    KeyCode key_code;
  };

  enum class Type {
    WindowResized,
    WindowClosed,
    WindowMinimized,
    WindowMaximized,
    MouseExited,
    MouseEntered,
    KeyPressed,
    KeyReleased,
    KeyDown,
    KeyUp
  };

  union {
    WindowResizeEvent window_resize;
    KeyPressedEvent key_pressed;
    KeyReleasedEvent key_released;
    bool empty = true;  // true for types that don't have any associated data
  };
  Type type;
};

}  // namespace prototype

#endif  // MINECPPRAFT_CORE_EVENT_H
