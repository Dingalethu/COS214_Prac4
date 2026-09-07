// main.cpp
#include <iostream>
#include "FireDepartment.h"
#include "PoliceDepartment.h"
#include "MedicalDepartment.h"
#include "EmergencyTask.h"

int main(){
    std::cout << "\n========== EMERGENCY RESPONSE SYSTEM ==========\n" << std::endl;
    
    FireDepartment* fireDept = new FireDepartment();
    PoliceDepartment* policeDept = new PoliceDepartment();
    MedicalDepartment* medicalDept = new MedicalDepartment();
    
    std::cout << "INITIAL RESOURCES:" << std::endl;
    std::cout << "Fire Trucks: " << fireDept->getNumTrucks() << std::endl;
    std::cout << "Police Cars: " << policeDept->getNumVehicles() << std::endl;
    std::cout << "Ambulances: " << medicalDept->getNumAmbulances() << std::endl;
    
    std::cout << "\n--- FIRE EMERGENCY ---" << std::endl;
    EmergencyTask* fireTask = new EmergencyTask("House Fire", fireDept, ResourceType::FireTruck);
    fireTask->executeResponse();
    std::cout << "Trucks left: " << fireDept->getNumTrucks() << std::endl;
    std::cout << "Allocated: " << fireTask->getAllocatedResources() << std::endl;
    
    fireTask->increaseResources(ResourceType::FireTruck, 2);
    std::cout << "Trucks left: " << fireDept->getNumTrucks() << std::endl;
    std::cout << "Allocated: " << fireTask->getAllocatedResources() << std::endl;
    
    fireTask->releaseResources(2);
    std::cout << "Trucks left: " << fireDept->getNumTrucks() << std::endl;
    std::cout << "Allocated: " << fireTask->getAllocatedResources() << std::endl;
    
    std::cout << "\n--- POLICE EMERGENCY ---" << std::endl;
    EmergencyTask* policeTask = new EmergencyTask("Bank Robbery", policeDept, ResourceType::PoliceCar);
    policeTask->executeResponse();
    std::cout << "Cars left: " << policeDept->getNumVehicles() << std::endl;
    std::cout << "Allocated: " << policeTask->getAllocatedResources() << std::endl;
    
    std::cout << "\n--- MEDICAL EMERGENCY ---" << std::endl;
    EmergencyTask* medicalTask = new EmergencyTask("Mass Casualty", medicalDept, ResourceType::Ambulance);
    medicalTask->executeResponse();
    std::cout << "Ambulances left: " << medicalDept->getNumAmbulances() << std::endl;
    std::cout << "Allocated: " << medicalTask->getAllocatedResources() << std::endl;
    
    delete fireTask;
    delete policeTask;
    delete medicalTask;
    delete fireDept;
    delete policeDept;
    delete medicalDept;
    
    std::cout <<"Termianting successfully" << std::endl;
    return 0;
}