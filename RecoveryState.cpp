#include "RecoveryState.h"
#include "EmergencyTask.h"
#include <iostream>

void RecoveryState::handleMobilization(EmergencyTask* task) {
    std::cout << "[" << task->getName() << "] Cannot mobilize: task is already in recovery." << std::endl;
}

void RecoveryState::handleWorkExecution(EmergencyTask* task) {
    std::cout << "[" << task->getName() << "] Cannot execute work: task is already in recovery." << std::endl;
}

void RecoveryState::handleRecovery(EmergencyTask* task) {
    std::cout << "[" << task->getName() << "] Recovery complete. Task is resolved." << std::endl;
}

std::string RecoveryState::getStateName() const {
    return "Recovery";
}
