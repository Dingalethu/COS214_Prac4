#include "Decorator.h"

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
