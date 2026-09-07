#ifndef EMERGENCYSTATE_H
#define EMERGENCYSTATE_H

#include <string>

class EmergencyTask;

class EmergencyState {
public:
    virtual ~EmergencyState() {}

    virtual void handleMobilization(EmergencyTask* task) = 0;
    virtual void handleWorkExecution(EmergencyTask* task) = 0;
    virtual void handleRecovery(EmergencyTask* task) = 0;
    virtual std::string getStateName() const = 0;
};

#endif