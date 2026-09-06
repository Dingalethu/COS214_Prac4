#include "PoliceDepartment.h"
#include <iostream>

PoliceDepartment::PoliceDepartment() : Composite("LAPD"){
    numVehicles = 200;
}


void PoliceDepartment::executeResponse(){
}


std::string PoliceDepartment::getName() const{
    return getName();
}

void PoliceDepartment::increaseResources(int amount){
    for(int i = 0; i < amount; i++){
        returnVehicle();
    }
}



int PoliceDepartment::getAllocatedResources() const{
    return 200 - numVehicles;
}


ResourceType PoliceDepartment::getResourceType() const{
    return ResourceType::Ambulance;
}


void PoliceDepartment::deployVehicle(){
    if(numVehicles > 0){
        numVehicles--;
    }
}



void PoliceDepartment::returnVehicle(){
    if(numVehicles != 200){
        numVehicles++;
    }
}


int PoliceDepartment::getNumVehicles() const{
    return numVehicles;
}


bool PoliceDepartment::allocateResources(ResourceType type, int amount){
    if(type != ResourceType::FireTruck){
        return false;
    }

    if(amount <= 0 || amount > numVehicles){
        std::cout << "Not enough trucks available" << std::endl;
        return false;
    }

    for(int i = 0; i < amount; i++){
        deployVehicle();
    }
    std::cout << "The LAPD has deployed " << amount << " police cars to the scene" << std::endl;
    return true;
}

void releaseResources(ResourceType type, int amount){
    // Must be implemented by the EmergencyTask
}