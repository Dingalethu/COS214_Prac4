// Composite.h
#ifndef COMPOSITE_H
#define COMPOSITE_H

#include "Component.h"
#include <vector>
#include <string>

class Composite : public Component {
private:
    std::vector<Component*> children;
    std::string name;
    bool isRespondingToEmergency;
    bool active;

public:
    Composite(const std::string& name);
    virtual ~Composite();

    // Component interface implementation
    void add(Component* component) override;
    void remove(Component* component) override;
    void executeResponse() override;
    void print() const override;
    std::string getName() const override;
    
    // Resource management (inherited from Component)
    void increaseResources(int amount) override;
    int getAllocatedResources() const override;
    ResourceType getResourceType() const override;

    virtual bool allocateResources(ResourceType type, int amount){}
    virtual void releaseResources(ResourceType type, int amount){}

    // Composite-specific methods
    void setResponding(bool);
    bool isActive() const;
    void setActive(bool);
};

#endif // COMPOSITE_H