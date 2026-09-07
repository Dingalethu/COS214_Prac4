#ifndef SAFETYCHECKDECORATOR_H
#define SAFETYCHECKDECORATOR_H

#include "Decorator.h"

class SafetyCheckDecorator : public Decorator {
private:
    bool equipmentReady;
    bool areaSafe;
    bool personnelReady;

public:
    SafetyCheckDecorator(Component* component);
    virtual ~SafetyCheckDecorator() {}

    void setEquipmentReady(bool ready);
    void setAreaSafe(bool safe);
    void setPersonnelReady(bool ready);
    bool isSafe() const;

    // Guards executeResponse behind safety check
    void executeResponse();

    bool isEquipmentReady() const { return equipmentReady; }
    bool isAreaSafe() const { return areaSafe; }
    bool isPersonnelReady() const { return personnelReady; }
};

#endif // SAFETYCHECKDECORATOR_H
