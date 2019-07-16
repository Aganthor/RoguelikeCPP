#pragma once

#include "Component.h"

namespace esc {

//
// A simple component to be able to represent the character to display
// for the Entity (e.g.: '@' for the player).
//

class AsciiComponent : public Component<AsciiComponent> {
public:
    char display;
};

}
