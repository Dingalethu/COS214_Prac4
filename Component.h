#ifndef COMPONENT_H
#define COMPONENT_H

#include <string>
#include <vector>

// Forward declarations so only the Iterator classes are granted access
// to the internal traversal hook below (see collectChildrenInto).
class CompleteDfsIterator;
class ActiveTaskIterator;

// Component: the shared interface for the Composite pattern.
// EmergencyTask (leaf) and Composite (composite) both implement this.
class Component {
    friend class CompleteDfsIterator;
    friend class ActiveTaskIterator;

public:
    virtual void add(Component* c);
    virtual void remove(Component* c);
    virtual void executeResponse() = 0;
    virtual std::string getName() const = 0;
    virtual void print(int depth = 0) const = 0;

    // Used by ActiveTaskIterator to decide whether a leaf task is currently
    // in progress. Composite aggregates this from its children.
    virtual bool isActive() const { return false; }

    // Resource-tracking hooks, pulled up here (rather than left only on
    // EmergencyTask) so Decorator can delegate through this shared
    // interface without knowing the concrete class it wraps.
    virtual void increaseResources(int amount) { (void)amount; }
    virtual void decreaseResources(int amount) { (void)amount; }
    virtual int  getAllocatedResources() const { return 0; }

    virtual ~Component() {}

protected:
    // Traversal-only hook: appends this node's children (if any) to out.
    // Protected and friended only to the two iterator classes, so client
    // code (main.cpp) can never call this to bypass the Iterator pattern
    // (rule: client may not obtain the internal container to traverse it).
    virtual void collectChildrenInto(std::vector<Component*>& out) const {
        (void)out; // leaves have no children by default
    }
};

#endif
