#include "PriorityDecorator.h"
#include <iostream>

PriorityDecorator::PriorityDecorator(Component* component, int priority)
    : Decorator(component), priority(priority) {}

void PriorityDecorator::setPriority(int p) {
    priority = p;
}

int PriorityDecorator::getPriority() const {
    return priority;
}

void PriorityDecorator::increaseResources(int amount) {
    if (priority > MAX_PRIORITY) {
        std::cout << "[PriorityDecorator] REJECTED: priority " << priority
                  << " exceeds maximum allowed (" << MAX_PRIORITY << ") for: "
                  << component->getName() << std::endl;
        return;
    }
    std::cout << "[PriorityDecorator] Priority " << priority
              << " - allocating " << amount << " resource(s) for: "
              << component->getName() << std::endl;
    component->increaseResources(amount);
}

void PriorityDecorator::executeResponse() {
    if (priority > MAX_PRIORITY) {
        std::cout << "[PriorityDecorator] REJECTED: priority " << priority
                  << " exceeds maximum. Response blocked for: "
                  << component->getName() << std::endl;
        return;
    }
    std::cout << "[PriorityDecorator] Dispatching response at priority "
              << priority << " for: " << component->getName() << std::endl;
    component->executeResponse();
}
