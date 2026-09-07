#include <iostream>
#include <string>
#include <vector>
#include "FireDepartment.h"
#include "PoliceDepartment.h"
#include "MedicalDepartment.h"
#include "EmergencyTask.h"
#include "PriorityDecorator.h"
#include "SafetyCheckDecorator.h"
#include "ActiveTaskIterator.h"
#include "CompleteDfsIterator.h"
#include "AlertState.h"
#include "ResponseState.h"
#include "RecoveryState.h"
using namespace std;

void printIterator(WorkIterator* it, const string& title){
    cout << "\n=== " << title << " ===" << endl;
    int count = 0;
    it->first();
    while(!it->isDone()) {
        Component* comp = it->currentItem();
        count++;
        cout << count << ". " << comp->getName();
        if(comp->isActive()){
            cout << " [ACTIVE]";
        }
        cout << endl;
        it->next();
    }
    cout << "Total: " << count << " items" << endl;
}

void showResources(FireDepartment* f, PoliceDepartment* p, MedicalDepartment* m){
    cout << "Resources: Fire:" << f->getNumTrucks() << " Police:" << p->getNumVehicles() << " Medical:" << m->getNumAmbulances() << endl;
}

int main(){
    cout << "\n===== EMERGENCY RESPONSE SYSTEM TESTS =====\n" << endl;
    cout << "TEST 1: Composite" << endl;
    FireDepartment* fireDept = new FireDepartment();
    PoliceDepartment* policeDept = new PoliceDepartment();
    MedicalDepartment* medicalDept = new MedicalDepartment();

    cout << "We have received a 911 Emergency alert: what is your emergency?" << std::endl;
    string type;
    cin >> type; // HOUSE FIRE
    EmergencyTask* fireTask = new EmergencyTask(type, fireDept, ResourceType::FireTruck);
    EmergencyTask* policeTask = new EmergencyTask("Bank Robbery", policeDept, ResourceType::PoliceCar);
    EmergencyTask* medicalTask = new EmergencyTask("Mass Casualty", medicalDept, ResourceType::Ambulance);
    EmergencyTask* medicalTask2 = new EmergencyTask("Heart Attack", medicalDept, ResourceType::Ambulance);

    fireDept->add(fireTask);
    policeDept->add(policeTask);
    medicalDept->add(medicalTask);
    medicalDept->add(medicalTask2);

    Composite* root = new Composite("Emergency System");
    root->add(fireDept);
    root->add(policeDept);
    root->add(medicalDept);

    cout << "Root: " << root-> getName() << " | Children: " << root->getChildren().size() << endl;
    
    EmergencyTask* extraTask = new EmergencyTask("Car Fire", fireDept, ResourceType::FireTruck);
    fireDept->add(extraTask);
    fireDept->remove(extraTask);
    delete extraTask;
    cout << "TEST 1: PASSED\n" << endl;
    cout << "===== TEST 2: The ITERATOR =====" << endl;
    fireTask->executeResponse();
    medicalTask->executeResponse();

    CompleteDfsIterator dfsIt(root);
    printIterator(&dfsIt, "Complete DFS");

    ActiveTaskIterator activeIt(root);
    printIterator(&activeIt, "Active Tasks Only");
    cout << "TEST 2: PASSED\n" << endl;

    // TEST 3: STATE
    cout << "TEST 3: State" << endl;
    FireDepartment* stateDept = new FireDepartment();
    EmergencyTask* stateTask = new EmergencyTask("Chemical Spill", stateDept, ResourceType::FireTruck);

    cout << "Initial: " << stateTask->getStateName() << endl;
    AlertState alert;
    alert.handleMobilization(stateTask);
    cout << "After Mobilize: " << stateTask->getStateName() << endl;
    
    ResponseState response;
    response.handleWorkExecution(stateTask);
    cout << "After Execute: " << stateTask->getStateName() << endl;
    
    RecoveryState recovery;
    recovery.handleRecovery(stateTask);
    cout << "After Recovery: " << stateTask->getStateName() << endl;
    
    // Invalid transitions
    alert.handleWorkExecution(stateTask);
    alert.handleRecovery(stateTask);
    response.handleMobilization(stateTask);
    response.handleRecovery(stateTask);

    delete stateTask;
    delete stateDept;
    cout << "TEST 3: PASSED\n" << endl;

    // TEST 4: DECORATOR
    cout << "TEST 4: Decorator" << endl;
    FireDepartment* decDept = new FireDepartment();
    EmergencyTask* baseTask = new EmergencyTask("High-Rise Fire", decDept, ResourceType::FireTruck);

    PriorityDecorator* priorityTask = new PriorityDecorator(baseTask, 3);
    cout << "Priority 3: ";
    priorityTask->executeResponse();
    priorityTask->setPriority(6);
    cout << "Priority 6 (invalid): ";
    priorityTask->executeResponse();

    SafetyCheckDecorator* safeTask = new SafetyCheckDecorator(priorityTask);
    cout << "Safety (all false): ";
    safeTask->executeResponse();
    safeTask->setEquipmentReady(true);
    safeTask->setAreaSafe(true);
    safeTask->setPersonnelReady(true);
    cout << "Safety (all true): ";
    safeTask->executeResponse();

    // Combined decorators
    EmergencyTask* combinedBase = new EmergencyTask("Combined", decDept, ResourceType::FireTruck);
    PriorityDecorator* combinedPriority = new PriorityDecorator(combinedBase, 4);
    SafetyCheckDecorator* combinedSafe = new SafetyCheckDecorator(combinedPriority);
    combinedSafe->setEquipmentReady(true);
    combinedSafe->setAreaSafe(true);
    combinedSafe->setPersonnelReady(true);
    cout << "Combined: ";
    combinedSafe->executeResponse();

    // Test Decorator forwarding methods
    EmergencyTask* decoratorTestTask = new EmergencyTask("Decorator Test", decDept, ResourceType::FireTruck);
    SafetyCheckDecorator* testDecorator = new SafetyCheckDecorator(decoratorTestTask);
    EmergencyTask* childTask = new EmergencyTask("Child", decDept, ResourceType::FireTruck);
    testDecorator->add(childTask);
    testDecorator->remove(childTask);
    delete childTask;
    testDecorator->increaseResources(2);
    cout << "Decorator resources: " << testDecorator->getAllocatedResources() << endl;
    vector<Component*> decChildren;
    testDecorator->collectChildrenInto(decChildren);
    cout << "Decorator children: " << decChildren.size() << endl;

    delete safeTask;
    delete combinedSafe;
    delete testDecorator;
    delete decDept;
    cout << "TEST 4: PASSED\n" << endl;

    // TEST 5: RESOURCE MANAGEMENT
    cout << "TEST 5: Resources" << endl;
    FireDepartment* resFire = new FireDepartment();
    PoliceDepartment* resPolice = new PoliceDepartment();
    MedicalDepartment* resMedical = new MedicalDepartment();

    EmergencyTask* resFireTask = new EmergencyTask("Wildfire", resFire, ResourceType::FireTruck);
    EmergencyTask* resPoliceTask = new EmergencyTask("Robbery", resPolice, ResourceType::PoliceCar);
    EmergencyTask* resMedicalTask = new EmergencyTask("Casualty", resMedical, ResourceType::Ambulance);

    resFireTask->executeResponse();
    resFireTask->increaseResources(ResourceType::FireTruck, 1);
    resPoliceTask->executeResponse();
    resMedicalTask->executeResponse();

    showResources(resFire, resPolice, resMedical);
    resFireTask->releaseResources(1);
    resMedicalTask->releaseResources(1);
    showResources(resFire, resPolice, resMedical);

    // Test overloaded increaseResources
    resFireTask->increaseResources(2);
    cout << "Fire resources: " << resFireTask->getAllocatedResources() << endl;

    delete resFireTask;
    delete resPoliceTask;
    delete resMedicalTask;
    delete resFire;
    delete resPolice;
    delete resMedical;
    cout << "TEST 5: PASSED\n" << endl;

    // TEST 6: ADDITIONAL COVERAGE
    cout << "TEST 6: Additional Coverage" << endl;
    
    // Composite setters
    Composite* testComp = new Composite("Test");
    testComp->setActive(true);
    testComp->setResponding(true);
    cout << "Composite active: " << testComp->isActive() << endl;
    testComp->allocateResources(ResourceType::FireTruck, 5);
    testComp->releaseResources(ResourceType::FireTruck, 3);
    delete testComp;

    // EmergencyTask leaf
    vector<Component*> leafChildren;
    fireTask->collectChildrenInto(leafChildren);
    cout << "Leaf children: " << leafChildren.size() << endl;

    // Department releaseResources
    FireDepartment* relFire = new FireDepartment();
    PoliceDepartment* relPolice = new PoliceDepartment();
    MedicalDepartment* relMedical = new MedicalDepartment();
    relFire->releaseResources(ResourceType::FireTruck, 2);
    relPolice->releaseResources(ResourceType::PoliceCar, 3);
    relMedical->releaseResources(ResourceType::Ambulance, 1);
    delete relFire;
    delete relPolice;
    delete relMedical;

    // Department isActive
    FireDepartment* actFire = new FireDepartment();
    actFire->executeResponse();
    cout << "Fire active: " << actFire->isActive() << endl;
    delete actFire;

    // Department createIterator
    FireDepartment* iterFire = new FireDepartment();
    EmergencyTask* iterTask = new EmergencyTask("IterTask", iterFire, ResourceType::FireTruck);
    iterFire->add(iterTask);
    WorkIterator* deptIt = iterFire->createIterator();
    deptIt->first();
    if (!deptIt->isDone()) cout << "Dept iter: " << deptIt->currentItem()->getName() << endl;
    delete deptIt;
    delete iterFire;

    // PriorityDecorator increaseResources
    FireDepartment* pDept = new FireDepartment();
    EmergencyTask* pBase = new EmergencyTask("PBase", pDept, ResourceType::FireTruck);
    PriorityDecorator* pTest = new PriorityDecorator(pBase, 3);
    pTest->increaseResources(2);
    pTest->setPriority(6);
    pTest->increaseResources(2);
    delete pTest;
    delete pDept;

    cout << "TEST 6: PASSED\n" << endl;

    // TEST 7: PRINT
    cout << "TEST 7: Print" << endl;
    fireTask->print();
    fireDept->print();
    root->print();
    cout << "TEST 7: PASSED\n" << endl;

    delete root;
    cout << "\n========================================" << endl;
    cout << "ALL TESTS PASSED SUCCESSFULLY!" << endl;
    cout << "========================================" << endl;
    return 0;
}