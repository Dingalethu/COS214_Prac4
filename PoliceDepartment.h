// PoliceDepartment.h
#ifndef POLICEDEPARTMENT_H
#define POLICEDEPARTMENT_H

#include "Composite.h"
#include "ResourceType.h"

class PoliceDepartment : public Composite {
private:
    int numVehicles;

public:
    PoliceDepartment();
    virtual ~PoliceDepartment();

    void executeResponse() override;
    void print() const override;
    std::string getName() const override;
    
    void increaseResources(int amount) override;
    int getAllocatedResources() const override;
    ResourceType getResourceType() const override;

    void deployVehicle();
    void returnVehicle();
    int getNumVehicles() const;
    bool allocateResources(ResourceType type, int amount);
    void releaseResources(ResourceType type, int amount);
};

#endif // POLICEDEPARTMENT_H