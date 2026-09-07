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
    
    void collectChildrenInto(std::vector<Component*>& out) const override;
    bool isActive() const override;

    // Exposes the wrapped component — allows callers to unwrap the decorator
    // chain when they need to access the concrete EmergencyTask beneath.
    Component* getComponent() const { return component; }

};

#endif // DECORATOR_H



