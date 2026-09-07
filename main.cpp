// main.cpp
#include <iostream>
#include <string>
#include <vector>
#include "Component.h"
#include "Composite.h"
#include "FireDepartment.h"
#include "PoliceDepartment.h"
#include "MedicalDepartment.h"
#include "EmergencyTask.h"
#include "AlertState.h"
#include "ResponseState.h"
#include "RecoveryState.h"
#include "SafetyCheckDecorator.h"
#include "PriorityDecorator.h"
#include "CompleteDfsIterator.h"
#include "ActiveTaskIterator.h"

Component* findTask(Composite* root, const std::string& name) {
    CompleteDfsIterator it(root);
    for (it.first(); !it.isDone(); it.next()) {
        Component* c = it.currentItem();
        if (c && c->getName() == name) return c;
    }
    return nullptr;
}

Composite* findParent(Composite* root, Component* child) {
    CompleteDfsIterator it(root);
    for (it.first(); !it.isDone(); it.next()) {
        Composite* comp = dynamic_cast<Composite*>(it.currentItem());
        if (comp) {
            std::vector<Component*> kids;
            comp->collectChildrenInto(kids);
            for (Component* k : kids)
                if (k == child) return comp;
        }
    }
    return nullptr;
}

// Unwraps one layer of decoration to get at the raw EmergencyTask underneath
EmergencyTask* resolveTask(Component* c) {
    if (!c) return nullptr;
    if (auto et = dynamic_cast<EmergencyTask*>(c)) return et;
    if (auto sd = dynamic_cast<SafetyCheckDecorator*>(c)) return dynamic_cast<EmergencyTask*>(sd->getComponent());
    if (auto pd = dynamic_cast<PriorityDecorator*>(c))    return dynamic_cast<EmergencyTask*>(pd->getComponent());
    return nullptr;
}

int main() {
    std::cout << "\n  TASKFORGE  |  Operation GitHappens\n";
    std::cout << "  Emergency Dispatch System\n";
    std::cout << "  --------------------------------------\n\n";

    // Build the composite hierarchy:
    //   CityGrid -> SectorAlpha -> LAFD  -> FactoryFire
    //            -> SectorBeta  -> LAPD  -> StreetRiot
    Composite* cityGrid    = new Composite("CityGrid");
    Composite* sectorAlpha = new Composite("SectorAlpha");
    Composite* sectorBeta  = new Composite("SectorBeta");

    FireDepartment*   alphaFire  = new FireDepartment();
    PoliceDepartment* betaPolice = new PoliceDepartment();

    cityGrid->add(sectorAlpha);
    cityGrid->add(sectorBeta);
    sectorAlpha->add(alphaFire);
    sectorBeta->add(betaPolice);

    EmergencyTask* fireTask = new EmergencyTask("FactoryFire", alphaFire, ResourceType::FireTruck);
    EmergencyTask* riotTask = new EmergencyTask("StreetRiot",  betaPolice, ResourceType::PoliceCar);
    alphaFire->add(fireTask);
    betaPolice->add(riotTask);

    std::cout << "  Active incidents:\n";
    std::cout << "    FactoryFire  [SectorAlpha / LAFD]\n";
    std::cout << "    StreetRiot   [SectorBeta  / LAPD]\n\n";

    std::string cmd;
    while (true) {
        std::cout << "\n> ";
        if (!(std::cin >> cmd)) break;

        if (cmd == "exit" || cmd == "quit") {
            break;

        } else if (cmd == "help") {
            std::cout << "\n  Commands:\n"
                      << "    status                      live DFS of the full city grid\n"
                      << "    active                      snapshot of active leaf tasks\n"
                      << "    dispatch   <task>           Alert -> Response + allocate resources\n"
                      << "    execute    <task>           Response -> Recovery\n"
                      << "    recover    <task>           close out task\n"
                      << "    escalate   <task>           wrap in SafetyCheckDecorator\n"
                      << "    secure     <task>           clear safety flags\n"
                      << "    prioritize <task> <1-5>     wrap in PriorityDecorator\n"
                      << "    newtask    <name> <alpha|beta> <fire|police|medical>\n"
                      << "    exit\n";

        } else if (cmd == "status") {
            std::cout << "\n  [CompleteDfsIterator -- live traversal]\n";
            CompleteDfsIterator it(cityGrid);
            for (it.first(); !it.isDone(); it.next()) {
                Component* c = it.currentItem();
                if (c)
                    std::cout << "    " << c->getName()
                              << "  (" << (c->isActive() ? "active" : "inactive") << ")\n";
            }

        } else if (cmd == "active") {
            std::cout << "\n  [ActiveTaskIterator -- snapshot of active leaves]\n";
            ActiveTaskIterator it(cityGrid);
            bool any = false;
            for (it.first(); !it.isDone(); it.next()) {
                Component* c = it.currentItem();
                if (c) { std::cout << "    " << c->getName() << "\n"; any = true; }
            }
            if (!any) std::cout << "    none\n";
            std::cout << "  (re-run to get a fresh snapshot after structural changes)\n";

        } else if (cmd == "dispatch") {
            std::string name; std::cin >> name;
            Component* t = findTask(cityGrid, name);
            if (!t) { std::cout << "  not found: " << name << "\n"; continue; }

            EmergencyTask* et = resolveTask(t);
            if (et) {
                AlertState trigger;
                trigger.handleMobilization(et);
                t->executeResponse();
            } else {
                std::cout << "  " << name << " is not a dispatchable task\n";
            }

        } else if (cmd == "execute") {
            std::string name; std::cin >> name;
            Component* t = findTask(cityGrid, name);
            if (!t) { std::cout << "  not found: " << name << "\n"; continue; }

            EmergencyTask* et = resolveTask(t);
            if (et) {
                ResponseState trigger;
                trigger.handleWorkExecution(et);
            } else {
                std::cout << "  " << name << " is not executable\n";
            }

        } else if (cmd == "recover") {
            std::string name; std::cin >> name;
            Component* t = findTask(cityGrid, name);
            if (!t) { std::cout << "  not found: " << name << "\n"; continue; }

            EmergencyTask* et = resolveTask(t);
            if (et) {
                RecoveryState trigger;
                trigger.handleRecovery(et);
            } else {
                std::cout << "  " << name << " is not recoverable\n";
            }

        } else if (cmd == "escalate") {
            std::string name; std::cin >> name;
            Component* t = findTask(cityGrid, name);
            if (!t) { std::cout << "  not found: " << name << "\n"; continue; }

            if (dynamic_cast<SafetyCheckDecorator*>(t)) {
                std::cout << "  " << name << " is already under safety protocols\n"; continue;
            }

            Composite* parent = findParent(cityGrid, t);
            if (parent) {
                parent->remove(t);
                parent->add(new SafetyCheckDecorator(t));
                std::cout << "  " << name << " wrapped in SafetyCheckDecorator -- use 'secure " << name << "' to clear\n";
            } else {
                std::cout << "  could not find parent for " << name << "\n";
            }

        } else if (cmd == "secure") {
            std::string name; std::cin >> name;
            Component* t = findTask(cityGrid, name);
            if (!t) { std::cout << "  not found: " << name << "\n"; continue; }

            SafetyCheckDecorator* sd = dynamic_cast<SafetyCheckDecorator*>(t);
            if (sd) {
                sd->setAreaSafe(true);
                sd->setEquipmentReady(true);
                sd->setPersonnelReady(true);
                std::cout << "  " << name << " -- all safety checks cleared\n";
            } else {
                std::cout << "  " << name << " has no active safety decorator\n";
            }

        } else if (cmd == "prioritize") {
            std::string name; std::cin >> name;
            int p = 3;
            if (!(std::cin >> p) || p < 1 || p > 5) {
                std::cin.clear();
                std::cin.ignore(1000, '\n');
                std::cout << "  priority must be 1-5\n"; continue;
            }

            Component* t = findTask(cityGrid, name);
            if (!t) { std::cout << "  not found: " << name << "\n"; continue; }

            if (dynamic_cast<PriorityDecorator*>(t)) {
                std::cout << "  " << name << " already has a priority decorator\n"; continue;
            }

            Composite* parent = findParent(cityGrid, t);
            if (parent) {
                parent->remove(t);
                parent->add(new PriorityDecorator(t, p));
                std::cout << "  " << name << " assigned priority " << p << "\n";
            } else {
                std::cout << "  could not find parent for " << name << "\n";
            }

        } else if (cmd == "newtask") {
            std::string name, sector, type;
            std::cin >> name >> sector >> type;

            Composite* dept = nullptr;
            ResourceType rtype = ResourceType::Personnel;

            if (sector == "alpha") {
                dept  = alphaFire;
                rtype = ResourceType::FireTruck;
            } else if (sector == "beta") {
                dept  = betaPolice;
                rtype = ResourceType::PoliceCar;
            } else {
                std::cout << "  unknown sector '" << sector << "' -- use alpha or beta\n"; continue;
            }

            if (type == "police")  rtype = ResourceType::PoliceCar;
            if (type == "medical") rtype = ResourceType::Ambulance;
            if (type == "fire")    rtype = ResourceType::FireTruck;

            if (findTask(cityGrid, name)) {
                std::cout << "  a task called '" << name << "' already exists\n"; continue;
            }

            dept->add(new EmergencyTask(name, dept, rtype));
            std::cout << "  added '" << name << "' to " << dept->getName() << " [" << sector << "]\n";

        } else {
            std::cout << "  unknown command -- type 'help'\n";
        }
    }

    std::cout << "\n  Shutting down...\n\n";
    std::cout << "  Traversal policy note:\n";
    std::cout << "    ActiveTaskIterator  -- snapshot (queue built at construction)\n";
    std::cout << "    CompleteDfsIterator -- live     (stack walks the tree as-is)\n\n";

    delete cityGrid;
    return 0;
}