// FireDepartment.h
#ifndef FIREDEPARTMENT_H
#define FIREDEPARTMENT_H

#include "Composite.h"
#include "ResourceType.h"

class FireDepartment : public Composite {
private:
    int numTrucks;

public:
    FireDepartment();
    virtual ~FireDepartment();

    void executeResponse() override;
    void print() const override;
    
    // Resource management (inherited from Component)
    void increaseResources(int amount) override;
    int getAllocatedResources() const override;
    ResourceType getResourceType() const override;

    // FireDepartment-specific methods
    void deployTruck();
    int getNumTrucks() const;
    void returnTruck();
    bool allocateResources(ResourceType type, int amount);
    void releaseResources(ResourceType type, int amount);
};

#endif // FIREDEPARTMENT_H