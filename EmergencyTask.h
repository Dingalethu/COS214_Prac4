#ifndef EMERGENCYTASK_H
#define EMERGENCYTASK_H
#include "Component.h"
#include "Composite.h"

class EmergencyState;

class EmergencyTask : public Component{
    private:
        EmergencyState* state;
        std::string emergencyType;
        Composite* resourceProvider;
        int allocatedResources;
        ResourceType resourceType;
    public:
        EmergencyTask(std::string EmergencyType, Composite* R_provider, ResourceType);
        void increaseResources(ResourceType type, int amount);
        void executeResponse();
        void releaseResources( int amount);
        int getAllocatedResources() const;
        ResourceType getResourceType();
};


#endif