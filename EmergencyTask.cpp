
#include "EmergencyTask.h"
#include <iostream>

EmergencyTask::EmergencyTask(std::string EmergencyType, Composite* R_provider, ResourceType rt){
    emergencyType = EmergencyType;
    state = nullptr;
    resourceProvider = R_provider;
    allocatedResources = 0;
    resourceType = rt;
}



void EmergencyTask::increaseResources(ResourceType type, int amount){
    std::cout << "=========== EMERGENCY TASK ASKING FOR MORE RESOURCES ===========" << std::endl;
    if(resourceProvider->allocateResources(resourceType, amount)){
        allocatedResources+= amount;
        std::cout << emergencyType << " has received " << amount << " more resources during the emergency" <<std::endl;;
    }
}


void EmergencyTask::executeResponse(){
    std::cout << "Attending to an emergency of type: " << emergencyType << std::endl;
    if(resourceProvider->allocateResources(resourceType, 1)){
        allocatedResources +=1;
    }
}


void EmergencyTask::releaseResources(int amount){
    std::cout << "Situation has stabilized - " << amount << " resources are being sent back" << std::endl;
    resourceProvider->increaseResources(amount);
}


int EmergencyTask::getAllocatedResources() const{
    return allocatedResources;
}


ResourceType EmergencyTask::getResourceType(){
    return resourceType;
}
