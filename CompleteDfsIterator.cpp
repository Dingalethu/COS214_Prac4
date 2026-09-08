#include "CompleteDfsIterator.h"
#include "Composite.h"

CompleteDfsIterator::CompleteDfsIterator(Composite* r) : root(r) {
    first();
}

CompleteDfsIterator::~CompleteDfsIterator() {}

void CompleteDfsIterator::first() {
    while (!traversalStack.empty()) traversalStack.pop();
    if (root) traversalStack.push(root);
}

bool CompleteDfsIterator::isDone() const {
    return traversalStack.empty();
}

Component* CompleteDfsIterator::currentItem() const {
    return traversalStack.empty() ? nullptr : traversalStack.top();
}

void CompleteDfsIterator::next() {
    if (traversalStack.empty()) return;

    Component* node = traversalStack.top();
    traversalStack.pop();

    std::vector<Component*> kids;
    node->collectChildrenInto(kids);

    // Push in reverse so the left-most child is the next one visited,
    // keeping a natural left-to-right pre-order.
    for (auto it = kids.rbegin(); it != kids.rend(); ++it) {
        traversalStack.push(*it);
    }
}
