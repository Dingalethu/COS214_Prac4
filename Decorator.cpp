#include "Decorator.h"
#include "Component.h"
#include <vector>

Decorator::Decorator(Component* component)
    : component(component) {}

Decorator::~Decorator() {
    delete component;
}

void Decorator::add(Component* c) {
    component->add(c);
}

void Decorator::remove(Component* c) {
    component->remove(c);
}

void Decorator::executeResponse() {
    component->executeResponse();
}

std::string Decorator::getName() const {
    return component->getName();
}

void Decorator::print() const {
    component->print();
}

void Decorator::increaseResources(int amount) {
    component->increaseResources(amount);
}

int Decorator::getAllocatedResources() const {
    return component->getAllocatedResources();
}

ResourceType Decorator::getResourceType() const {
    return component->getResourceType();
}



void Decorator::collectChildrenInto(std::vector<Component*>& out) const{
    component->collectChildrenInto(out);
}
    
bool Decorator::isActive() const{
    return component->isActive();
}
