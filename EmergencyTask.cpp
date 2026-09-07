#include "EmergencyTask.h"
#include <iostream>

EmergencyTask::EmergencyTask(const std::string& n, bool responding)
    : name(n), respondingNow(responding) {}

EmergencyTask::~EmergencyTask() {}

void EmergencyTask::executeResponse() {
    std::cout << "Executing task: " << name
              << (respondingNow ? " [ACTIVE]" : "") << "\n";
}

std::string EmergencyTask::getName() const {
    return name;
}

void EmergencyTask::print(int depth) const {
    std::cout << std::string(depth * 2, ' ') << "* " << name
              << (respondingNow ? " (active)" : "") << "\n";
}

bool EmergencyTask::isActive() const {
    return respondingNow;
}

void EmergencyTask::setResponding(bool responding) {
    respondingNow = responding;
}
