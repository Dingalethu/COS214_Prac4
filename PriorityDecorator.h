#ifndef PRIORITYDECORATOR_H
#define PRIORITYDECORATOR_H

#include "Decorator.h"

#define MAX_PRIORITY 5

class PriorityDecorator : public Decorator {
private:
    int priority;

public:
    PriorityDecorator(Component* component, int priority);
    virtual ~PriorityDecorator() {}

    void setPriority(int priority);
    int  getPriority() const;

    // Intercepts resource increase — scales by priority, rejects if priority > MAX
    void increaseResources(int amount);
    void executeResponse();
};

#endif // PRIORITYDECORATOR_H
