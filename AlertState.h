#ifndef ALERTSTATE_H
#define ALERTSTATE_H

#include "EmergencyState.h"

class AlertState : public EmergencyState {
public:
    virtual ~AlertState() {}
    
    void handleMobilization(EmergencyTask* task);
    void handleWorkExecution(EmergencyTask* task);
    void handleRecovery(EmergencyTask* task);
    std::string getStateName() const;
};

#endif