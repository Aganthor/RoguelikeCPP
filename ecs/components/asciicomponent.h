#pragma once

#include "../../include/libtcod.hpp"
#include "../Component.h"

namespace ecs {

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
