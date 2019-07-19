#pragma once

#include "Component.h"
#include "../../include/libtcod.hpp"

namespace esc {

//
// A simple component to be able to represent the character to display
// for the Entity (e.g.: '@' for the player).
//

struct AsciiComponent : public Component<AsciiComponent> {
  AsciiComponent(char ch, TCODColor pcolor) : character{ch}, color{pcolor} {}

  char character{' '};
  TCODColor color {TCODColor::white};
};

}  // namespace esc
