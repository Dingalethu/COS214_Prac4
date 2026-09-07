#include "MedicalDepartment.h"
#include <iostream>

MedicalDepartment::MedicalDepartment() : Composite("Cedars-Sinai Medical Center"){
    numAmbulances = 15;
}

MedicalDepartment::~MedicalDepartment(){}

void MedicalDepartment::executeResponse(){
    deployAmbulance();
}

// MedicalDepartment.cpp - Update print() method
void MedicalDepartment::print() const{
    std::cout << "===================== MEDICAL RESPONSE =====================" << std::endl;
    std::cout << "The Cedars-Sinai Medical Center is responding to a medical alert" << std::endl;
    std::cout << (15 - numAmbulances) << " ambulances have been deployed" << std::endl;  // Fixed spacing and wording
}


std::string MedicalDepartment::getName() const{
    return "Cedars-Sinai Medical Center";
}



void MedicalDepartment::increaseResources(int amount){
    std::cout << "Resources are being returned back to the MEDICAL department after an emergency response" << std::endl;
    if(amount <= numAmbulances){
        for(int i = 0; i < amount; i++){
            returnAmbulance();
        }
    }
}

int MedicalDepartment::getAllocatedResources() const{
    return 15 - numAmbulances;
}



ResourceType MedicalDepartment::getResourceType() const {
    return ResourceType::Ambulance;
}


void MedicalDepartment::deployAmbulance(){
    if(numAmbulances > 0){
        --numAmbulances;
    }
}

void MedicalDepartment::returnAmbulance(){
    if(numAmbulances != 15){
        numAmbulances++;
    }

}

int MedicalDepartment::getNumAmbulances() const{
    return numAmbulances;
}


bool MedicalDepartment::allocateResources(ResourceType type, int amount){
    if(type != ResourceType::Ambulance){
        return false;
    }
    if(amount > numAmbulances){
        return false;
    }
    std::cout << "The Medical Center has deployed " << amount << " ambulances to the scene" << std::endl;
    numAmbulances-=amount;
    return true;
}

void MedicalDepartment::releaseResources(ResourceType type, int amount){}

