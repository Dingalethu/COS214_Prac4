#ifndef EMERGENCYTASK_H
#define EMERGENCYTASK_H

#include "Component.h"
#include <string>

// EmergencyTask: the Leaf. Represents one individual piece of work,
// e.g. "Extinguish Fire". Has no children.
//
// NOTE: 'respondingNow' is a temporary stand-in for "currently in
// ResponseState". Once EmergencyState/AlertState/ResponseState/
// RecoveryState exist, replace isActive() below with a check against
// the task's current state instead of this raw bool.
class EmergencyTask : public Component {
public:
    explicit EmergencyTask(const std::string& name, bool respondingNow = false);
    ~EmergencyTask() override;

    void executeResponse() override;
    std::string getName() const override;
    void print(int depth = 0) const override;
    bool isActive() const override;

    void setResponding(bool responding);

private:
    std::string name;
    bool respondingNow;
};

#endif
