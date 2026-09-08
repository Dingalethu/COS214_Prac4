#ifndef RECOVERYSTATE_H
#define RECOVERYSTATE_H

#include "EmergencyState.h"

class RecoveryState : public EmergencyState {
public:
    virtual ~RecoveryState() {}

    void handleMobilization(EmergencyTask* task);
    void handleWorkExecution(EmergencyTask* task);
    void handleRecovery(EmergencyTask* task);
    std::string getStateName() const;
};

#endif
