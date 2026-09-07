
#include "EmergencyTask.h"
#include "EmergencyState.h"
#include "AlertState.h"
#include <iostream>


EmergencyTask::~EmergencyTask(){
    if(state){
        delete state;
    }
}
EmergencyTask::EmergencyTask(std::string EmergencyType, Composite* R_provider, ResourceType rt){
    emergencyType = EmergencyType;
    state = new AlertState(); 
    resourceProvider = R_provider;
    allocatedResources = 0;
    resourceType = rt;
    active = true;
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
     if(amount > allocatedResources){
        amount = allocatedResources;
    }
    std::cout << "Situation has stabilized - " << amount << " resources are being sent back" << std::endl;
    resourceProvider->increaseResources(amount);
    allocatedResources -= amount;

}


int EmergencyTask::getAllocatedResources() const{
    return allocatedResources;
}


ResourceType EmergencyTask::getResourceType() const{
    return resourceType;
}

void EmergencyTask::print() const {
    std::cout << "Emergency Task: " << emergencyType << std::endl;
    std::cout << "  State: " << state->getStateName() << std::endl;
    std::cout << "  Resources: " << allocatedResources << std::endl;
    std::cout << "  Active: " << (active ? "Yes" : "No") << std::endl;
}

void EmergencyTask::setState(EmergencyState* newState) {
    delete state;
    state = newState;
}

bool EmergencyTask::isActive() const{
    return active;
}

std::string EmergencyTask::getStateName() const{
    if(state){
        return state-> getStateName();
    }else{
        return "Unknown State";
    }
}


std::string EmergencyTask::getName() const{
    return emergencyType;
}

void EmergencyTask::increaseResources(int amount){
    increaseResources(resourceType, amount);
}

void EmergencyTask::collectChildrenInto(std::vector<Component*>& out) const{
}