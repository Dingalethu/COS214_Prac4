#include "ResponseState.h"
#include "RecoveryState.h"
#include "EmergencyTask.h"
#include <iostream>

void ResponseState::handleMobilization(EmergencyTask* task) {
    std::cout << "[" << task->getName() << "] Cannot mobilize: task is already in active response." << std::endl;
}

void ResponseState::handleWorkExecution(EmergencyTask* task) {
    std::cout << "[" << task->getName() << "] Executing response work. Transitioning to Recovery." << std::endl;
    task->setState(new RecoveryState());
}

void ResponseState::handleRecovery(EmergencyTask* task) {
    std::cout << "[" << task->getName() << "] Cannot begin recovery: work execution has not completed yet." << std::endl;
}

std::string ResponseState::getStateName() const {
    return "Response";
}
