#ifndef COMPOSITE_H
#define COMPOSITE_H

#include "Component.h"
#include <string>
#include <vector>

class WorkIterator; // only the pointer type is needed here

// Composite: used at every internal level of the tree (Department,
// Battalion, Unit, ...). Owns and deletes its children.
class Composite : public Component {
public:
    explicit Composite(const std::string& name);
    ~Composite() override;

    void add(Component* c) override;
    void remove(Component* c) override;
    void executeResponse() override;
    std::string getName() const override;
    void print(int depth = 0) const override;
    bool isActive() const override;

    // Aggregate role: factory methods hand back an abstract WorkIterator,
    // never the internal container itself (rule: no exposing the container
    // just so the client can loop over it).
    WorkIterator* createCompleteIterator();
    WorkIterator* createActiveIterator();

protected:
    void collectChildrenInto(std::vector<Component*>& out) const override;

private:
    std::string name;
    std::vector<Component*> children;
};

#endif
