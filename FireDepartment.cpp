#include "FireDepartment.h"
#include "ResourceType.h"
#include <iostream>
#include "CompleteDfsIterator.h" 

FireDepartment::FireDepartment() : Composite("LAFD"){
    numTrucks = 10;
}

FireDepartment::~FireDepartment(){}


void FireDepartment::executeResponse(){
    Composite::executeResponse();
    deployTruck();
    deployTruck();
}


void FireDepartment::print() const{
    std::cout << "===================== FIRE RESPONSE =====================" << std::endl;
    std::cout << "The Los Angeles Fire Department is responding to a fire alert" << std::endl;
    std::cout << (10 - numTrucks) << " trucks have been deployed" << std::endl;  // Dynamic calculation
}

void FireDepartment::increaseResources(int amount){
    std::cout << "Resources are being returned back to the LAFD department after an emergency response" << std::endl;
    for(int i = 0; i < amount; i++){
        returnTruck();
    }  
}


int FireDepartment::getAllocatedResources() const{
    return 10 - numTrucks;
}


ResourceType FireDepartment::getResourceType() const{
    return ResourceType::FireTruck;
}


void FireDepartment::deployTruck(){
    if(numTrucks > 0){
        --numTrucks;
    }
}



int FireDepartment::getNumTrucks() const{
    return numTrucks;
}


void FireDepartment::returnTruck(){
    if(numTrucks < 10) {
        ++numTrucks;
    }
}


bool FireDepartment::allocateResources(ResourceType type, int amount){
    if(type != ResourceType::FireTruck){
        return false;
    }

    if (amount <= 0 || amount > numTrucks){
        std::cout << "Not enough trucks available" << std::endl;
        return false;
    }

    for(int i = 0; i < amount; i++){
        deployTruck();
    }
    std::cout << "The LAFD has deployed " << amount << " Fire trucks to the scene" << std::endl;
    return true;
}



void FireDepartment::releaseResources(ResourceType type, int amount){
    if(type == ResourceType::FireTruck) {
        increaseResources(amount);
    }
}


bool FireDepartment::isActive() const{
    return Composite::isActive();
}


WorkIterator* FireDepartment::createIterator(){
    return new CompleteDfsIterator(this);
}