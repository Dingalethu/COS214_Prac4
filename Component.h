#ifndef COMPONENT_H
#define COMPONENT_H

#include <string>
#include "ResourceType.h"
#include <vector>

class Component {
public:
    virtual ~Component() ;

    virtual void add(Component* component) = 0;
    virtual void remove(Component* component) = 0;
    
    virtual void executeResponse() = 0;
    virtual std::string getName() const = 0;
    virtual void print() const = 0;
    
    virtual void increaseResources(int amount) = 0;
    virtual int getAllocatedResources() const = 0;
    virtual ResourceType getResourceType() const = 0;

    virtual void collectChildrenInto(std::vector<Component*>& out) const = 0;
    virtual bool isActive() const = 0;
};

#endif // COMPONENT_H