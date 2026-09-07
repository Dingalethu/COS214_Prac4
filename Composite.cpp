#include "Composite.h"
#include "CompleteDfsIterator.h"
#include <iostream>

Composite::Composite(const std::string& name){
    this-> name = name;
    isRespondingToEmergency = false;
    active = false;
}

Composite::~Composite(){
    if(!children.empty()){
        for(Component* child : children){
            if(child){
                delete child;
            }
        }
    }
}

void Composite::add(Component* component){
    children.push_back(component);
}


void Composite::remove(Component* component) {
    for(auto it = children.begin(); it != children.end(); ++it){
        if(*it == component){
            children.erase(it);  
            return;
        }
    }
}


void Composite::executeResponse(){
    isRespondingToEmergency = true;
    active = true;
}


std::string Composite::getName()const{
    return name;
}


void Composite::print() const{
    std::cout << "Composite: " << name << std::endl;
    std::cout << "Active: " << (active ? "Yes" : "No") << std::endl;
    std::cout << "Responding: " << (isRespondingToEmergency ? "Yes" : "No") << std::endl;
    std::cout << "Number of children: " << children.size() << std::endl;
    
    if(!children.empty()){
        std::cout << "Printing children:" << std::endl;
        for(const Component* child : children){
            child->print();
            std::cout << std::endl;
        }
    }
}
void Composite::increaseResources(int amount){}

int Composite::getAllocatedResources() const {
     return 0; 
}

ResourceType Composite::getResourceType() const {
     return ResourceType::Personnel; 
}

void Composite::setResponding(bool responding){
    isRespondingToEmergency = responding;
}

bool Composite::isActive() const{
    return active; 
}

void Composite::setActive(bool isActive){
    active = isActive;
}

WorkIterator* Composite::createIterator() {
    return new CompleteDfsIterator(this);
}


void Composite::collectChildrenInto(std::vector<Component*>& out) const {
    for (Component* c : children) {
        out.push_back(c);
    }
}
