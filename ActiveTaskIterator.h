#ifndef ACTIVETASKITERATOR_H
#define ACTIVETASKITERATOR_H

#include "WorkIterator.h"
#include "Component.h"
#include <queue>
#include <vector>

class Composite; // forward declaration avoids a circular include with Composite.h

// ActiveTaskIterator: visits only leaf EmergencyTasks whose isActive() is
// true. The queue is built once, at construction time -- a deliberate
// SNAPSHOT policy, contrasted with CompleteDfsIterator's live stack-based
// walk. If the tree changes after this iterator is created, it will not
// pick up new active tasks; that trade-off is our documented traversal-
// modification policy for Task 3.
class ActiveTaskIterator : public WorkIterator {
public:
    explicit ActiveTaskIterator(Composite* root);
    ~ActiveTaskIterator() override;

    void first() override;
    void next() override;
    bool isDone() const override;
    Component* currentItem() const override;

private:
    Composite* root;
    std::queue<Component*> leafQueue;

    void findNextActiveLeaf(Component* node);
};

#endif
