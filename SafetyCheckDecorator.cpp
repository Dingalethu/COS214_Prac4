#include "SafetyCheckDecorator.h"
#include <iostream>

SafetyCheckDecorator::SafetyCheckDecorator(Component* component)
    : Decorator(component),
      equipmentReady(false),
      areaSafe(false),
      personnelReady(false) {}

void SafetyCheckDecorator::setEquipmentReady(bool ready) {
    equipmentReady = ready;
}

void SafetyCheckDecorator::setAreaSafe(bool safe) {
    areaSafe = safe;
}

void SafetyCheckDecorator::setPersonnelReady(bool ready) {
    personnelReady = ready;
}

bool SafetyCheckDecorator::isSafe() const {
    return equipmentReady && areaSafe && personnelReady;
}

void SafetyCheckDecorator::executeResponse() {
    if (!isSafe()) {
        std::cout << "[SafetyCheckDecorator] SAFETY CHECK FAILED for: "
                  << component->getName() << std::endl;
        if (!equipmentReady)  std::cout << "  - Equipment not ready" << std::endl;
        if (!areaSafe)        std::cout << "  - Area not safe" << std::endl;
        if (!personnelReady)  std::cout << "  - Personnel not ready" << std::endl;
        std::cout << "  Response blocked until all safety conditions are met." << std::endl;
        return;
    }
    std::cout << "[SafetyCheckDecorator] All safety checks passed for: "
              << component->getName() << std::endl;
    component->executeResponse();
}
