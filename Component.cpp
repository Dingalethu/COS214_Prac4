#include "Component.h"
#include <iostream>

// Default behaviour for the "unsafe interface" trade-off: add/remove are
// declared on Component (so client code can call them uniformly), but a
// leaf has no children, so the base implementation reports the misuse
// sensibly instead of crashing.
void Component::add(Component* /*c*/) {
    std::cout << "[warning] add() is not supported on '" << getName() << "'\n";
}

void Component::remove(Component* /*c*/) {
    std::cout << "[warning] remove() is not supported on '" << getName() << "'\n";
}
