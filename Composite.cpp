#include "Composite.h"

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


void Composite::remove(Component* component){
       if(!children.empty()){
        for(Component* child : children){
            if(child == component){
                delete child;
                child = nullptr;
            }
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

void Composite::print() const{}
void Composite::increaseResources(int amount){}
int Composite::getAllocatedResources() const{}
void Composite::decreaseResources(int amount){}
ResourceType Composite::getResourceType() const{}

void Composite::setResponding(bool){}
bool Composite::isActive() const{}
void Composite::setActive(bool){}