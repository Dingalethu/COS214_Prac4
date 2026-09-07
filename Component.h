#ifndef COMPONENT_H
#define COMPONENT_H

#include <string>
#include "ResourceType.h"

class Component {
public:
    virtual ~Component() ;

    // Composite pattern methods
    virtual void add(Component* component) = 0;
    virtual void remove(Component* component) = 0;
    
    // Core functionality
    virtual void executeResponse() = 0;
    virtual std::string getName() const = 0;
    virtual void print() const = 0;
    
    // Resource management
    virtual void increaseResources(int amount) = 0;
    virtual int getAllocatedResources() const = 0;
    virtual ResourceType getResourceType() const = 0;
};

#endif // COMPONENT_H