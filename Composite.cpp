#include "Composite.h"
#include "CompleteDfsIterator.h"
#include "ActiveTaskIterator.h"
#include <algorithm>
#include <iostream>

Composite::Composite(const std::string& n) : name(n) {}

Composite::~Composite() {
    for (Component* c : children) {
        delete c; // ownership: Composite owns and deletes its children
    }
}

void Composite::add(Component* c) {
    children.push_back(c);
}

void Composite::remove(Component* c) {
    children.erase(std::remove(children.begin(), children.end(), c), children.end());
}

void Composite::executeResponse() {
    for (Component* c : children) {
        c->executeResponse();
    }
}

std::string Composite::getName() const {
    return name;
}

void Composite::print(int depth) const {
    std::cout << std::string(depth * 2, ' ') << "- " << name << "\n";
    for (Component* c : children) {
        c->print(depth + 1);
    }
}

bool Composite::isActive() const {
    for (Component* c : children) {
        if (c->isActive()) return true;
    }
    return false;
}

void Composite::collectChildrenInto(std::vector<Component*>& out) const {
    for (Component* c : children) {
        out.push_back(c);
    }
}

WorkIterator* Composite::createCompleteIterator() {
    return new CompleteDfsIterator(this);
}

WorkIterator* Composite::createActiveIterator() {
    return new ActiveTaskIterator(this);
}
