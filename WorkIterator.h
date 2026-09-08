#ifndef WORKITERATOR_H
#define WORKITERATOR_H

class Component;

// WorkIterator: the abstract Iterator interface (GoF Iterator participant).
// main.cpp only ever sees this interface -- never the concrete iterator
// classes below, and never Composite's internal child list.
class WorkIterator {
public:
    virtual void first() = 0;
    virtual void next() = 0;
    virtual bool isDone() const = 0;
    virtual Component* currentItem() const = 0;
    virtual ~WorkIterator() {}
};

#endif
