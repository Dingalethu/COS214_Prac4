#ifndef COMPOSITE_H
#define COMPOSITE_H

#include "Component.h"
#include "WorkIterator.h"
#include <vector>
#include <string>

class Composite : public Component{
private:
    std::vector<Component*> children;
    std::string name;
    bool isRespondingToEmergency;
    bool active;

public:
    Composite(const std::string& name);
    virtual ~Composite();

    void add(Component* component) override;
    void remove(Component* component) override;
    void executeResponse() override;
    void print() const override;
    std::string getName() const override;
    
    void increaseResources(int amount) override;
    int getAllocatedResources() const override;
    ResourceType getResourceType() const override;

    void collectChildrenInto(std::vector<Component*>& out) const;

    virtual bool allocateResources(ResourceType type, int amount) { return false; }
    virtual void releaseResources(ResourceType type, int amount) {}

    void setResponding(bool);
    bool isActive() const override;
    void setActive(bool);

    const std::vector<Component*>& getChildren() const { return children; }
    virtual WorkIterator* createIterator();
};

#endif