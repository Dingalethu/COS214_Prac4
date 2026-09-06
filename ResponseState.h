#ifndef RESPONSESTATE_H
#define RESPONSESTATE_H

#include "EmergencyState.h"

class ResponseState : public EmergencyState {
public:
    virtual ~ResponseState() {}

    void handleMobilization(EmergencyTask* task);
    void handleWorkExecution(EmergencyTask* task);
    void handleRecovery(EmergencyTask* task);
    std::string getStateName() const;
};

#endif