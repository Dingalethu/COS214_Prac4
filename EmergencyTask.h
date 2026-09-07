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
        bool active;

    public:
        ~EmergencyTask();
        EmergencyTask(std::string EmergencyType, Composite* R_provider, ResourceType);
        void increaseResources(ResourceType type, int amount);
        void executeResponse() override;
        void releaseResources( int amount);
        int getAllocatedResources() const;
        ResourceType getResourceType() const;
        virtual void add(Component* component){}
        virtual void remove(Component* component){}
        
        virtual std::string getName() const;
        virtual void print() const;
        virtual void increaseResources(int amount);
        void collectChildrenInto(std::vector<Component*>& out) const override;

        // state Context Functions
        void setState(EmergencyState* newState);

        bool isActive() const override;
        std::string getStateName() const;
        
};


#endif