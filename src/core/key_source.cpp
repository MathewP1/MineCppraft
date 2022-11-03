//
// Created by Mateusz Palkowski on 03/11/2022.
//
#include "key_source.h"

#include "keyboard.h"

namespace prototype {
KeySource* KeySource::s_key_source_ = nullptr;

KeySource& KeySource::Get() { return *s_key_source_; }

void KeySource::OnGLFWKey(int key, int scancode, int action, int mods) {
  // TODO: fire pressed and released callbacks, on state change fire key up or key down
}

}