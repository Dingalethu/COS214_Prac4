#include "ActiveTaskIterator.h"
#include "Composite.h"

ActiveTaskIterator::ActiveTaskIterator(Composite* r) : root(r) {
    first();
}

ActiveTaskIterator::~ActiveTaskIterator() {}

void ActiveTaskIterator::first() {
    while (!leafQueue.empty()) leafQueue.pop();
    if (root) findNextActiveLeaf(root);
}

void ActiveTaskIterator::findNextActiveLeaf(Component* node) {
    std::vector<Component*> kids;
    node->collectChildrenInto(kids);

    if (kids.empty()) {
        // No children reported -> this is a leaf (or an empty group).
        if (node->isActive()) {
            leafQueue.push(node);
        }
        return;
    }

    for (Component* child : kids) {
        findNextActiveLeaf(child);
    }
}

bool ActiveTaskIterator::isDone() const {
    return leafQueue.empty();
}

Component* ActiveTaskIterator::currentItem() const {
    return leafQueue.empty() ? nullptr : leafQueue.front();
}

void ActiveTaskIterator::next() {
    if (!leafQueue.empty()) {
        leafQueue.pop();
    }
}
