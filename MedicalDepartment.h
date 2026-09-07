// MedicalDepartment.h
#ifndef MEDICALDEPARTMENT_H
#define MEDICALDEPARTMENT_H

#include "Composite.h"
#include "ResourceType.h"

class MedicalDepartment : public Composite {
private:
    int numAmbulances;

public:
    MedicalDepartment();
    virtual ~MedicalDepartment();

    void executeResponse() override;
    void print() const override;
    std::string getName() const override;
    
    void increaseResources(int amount) override;
    int getAllocatedResources() const override;
    ResourceType getResourceType() const override;

    void deployAmbulance();
    void returnAmbulance();
    int getNumAmbulances() const;
    bool allocateResources(ResourceType type, int amount);
    void releaseResources(ResourceType type, int amount);

    bool isActive() const override;
};

#endif // MEDICALDEPARTMENT_H