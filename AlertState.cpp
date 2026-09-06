#include "AlertState.h"
#include "ResponseState.h"
#include "EmergencyTask.h"
#include <iostream>

void AlertState::handleMobilization(EmergencyTask* task) {
    std::cout << "[" << task->getName() << "] Mobilizing resources. Transitioning to Response." << std::endl;
    task->setState(new ResponseState());
}

void AlertState::handleWorkExecution(EmergencyTask* task) {
    std::cout << "[" << task->getName() << "] Cannot execute work: task has not been mobilized yet." << std::endl;
}

void AlertState::handleRecovery(EmergencyTask* task) {
    std::cout << "[" << task->getName() << "] Cannot begin recovery: task has not been mobilized or executed yet." << std::endl;
}

std::string AlertState::getStateName() const {
    return "Alert";
}