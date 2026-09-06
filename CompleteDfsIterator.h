#ifndef COMPLETEDFSITERATOR_H
#define COMPLETEDFSITERATOR_H

#include "WorkIterator.h"
#include "Component.h"
#include <stack>
#include <vector>

class Composite; // forward declaration avoids a circular include with Composite.h

// CompleteDfsIterator: visits every Component (composites AND leaves)
// reachable from root, in pre-order, via an explicit stack over the LIVE
// tree. This is the traversal that satisfies "at least one traversal must
// visit the complete structure" -- used for the after-action report.
class CompleteDfsIterator : public WorkIterator {
public:
    explicit CompleteDfsIterator(Composite* root);
    ~CompleteDfsIterator() override;

    void first() override;
    void next() override;
    bool isDone() const override;
    Component* currentItem() const override;

private:
    Composite* root;
    std::stack<Component*> traversalStack;
};

#endif
