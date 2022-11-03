//
// Created by Mateusz Palkowski on 03/11/2022.
//

#ifndef MINECPPRAFT_CORE_KEY_SOURCE_H
#define MINECPPRAFT_CORE_KEY_SOURCE_H

namespace prototype {

class KeySource {
 public:
  static KeySource& Get();
  void OnGLFWKey(int key, int scancode, int action, int mods);

 private:
  static KeySource* s_key_source_;
};

}  // namespace prototype

#endif  // MINECPPRAFT_CORE_KEY_SOURCE_H
