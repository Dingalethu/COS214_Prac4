#ifndef DECORATOR_H
#define DECORATOR_H

#include "Component.h"

class Decorator : public Component {
protected:
    Component* component;

public:
    Decorator(Component* component);
    virtual ~Decorator();

    // Forwarding — concrete decorators override only what they change
    void add(Component* c);
    void remove(Component* c);
    void executeResponse();
    std::string getName() const;
    void print() const;

    void increaseResources(int amount);
    int  getAllocatedResources() const;
    ResourceType getResourceType() const;
};

#endif // DECORATOR_H
