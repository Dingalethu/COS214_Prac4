#include "PoliceDepartment.h"
#include <iostream>

PoliceDepartment::PoliceDepartment() : Composite("LAPD"){
    numVehicles = 200;
}


void PoliceDepartment::executeResponse(){
    Composite::executeResponse();
    if(numVehicles >=5){
        for(int i = 0; i < 5; i++){
            deployVehicle();
        }
        std::cout << "LAPD dispatching police units to the scene" << std::endl;
        return;
    }

    std::cout << "LAPD not responding due to lack of resources" << std::endl;
}


std::string PoliceDepartment::getName() const{
    return "LAPD";
}

void PoliceDepartment::increaseResources(int amount){
    std::cout << "Resources are being returned back to the LAPD department after an emergency response" << std::endl;
    for(int i = 0; i < amount; i++){
        returnVehicle();
    }
}



int PoliceDepartment::getAllocatedResources() const{
    return 200 - numVehicles;
}


ResourceType PoliceDepartment::getResourceType() const{
    return ResourceType::PoliceCar;
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
    if(type != ResourceType::PoliceCar){
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

void PoliceDepartment::print() const{
    std::cout << "===================== POLICE RESPONSE =====================" << std::endl;
    std::cout << "The Los Angeles Police Department is responding to a police alert" << std::endl;  // Fixed
    std::cout << (200 - numVehicles) << " police cars have been deployed" << std::endl;  // Fixed
}


void PoliceDepartment::releaseResources(ResourceType type, int amount){
    if(type == ResourceType::PoliceCar) {
        increaseResources(amount);
    }
}

PoliceDepartment::~PoliceDepartment(){}



bool PoliceDepartment::isActive() const {
    return Composite::isActive();
}