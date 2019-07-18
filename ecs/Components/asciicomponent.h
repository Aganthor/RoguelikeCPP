#pragma once

#include "Component.h"

namespace esc {

//
// A simple component to be able to represent the character to display
// for the Entity (e.g.: '@' for the player).
//

struct AsciiComponent : public Component<AsciiComponent> {
  AsciiComponent(char ch) : display{ch} {}
  char display{' '};
};

}  // namespace esc
