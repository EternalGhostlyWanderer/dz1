#include "inspection/ServiceCenter.h"

#include "enums/EquipmentCondition.h"
#include "enums/InspectionResult.h"

Inspection ServiceCenter::inspect(const Inventoriable& item) {
    if (isAllowed(item)) {
        return Inspection(InspectionResult::PASSED);
    }

    return Inspection(InspectionResult::FAILED);
}

bool ServiceCenter::isAllowed(const Inventoriable& item) const {
    const EquipmentCondition condition = item.getCondition();

    return condition == EquipmentCondition::NEW ||
           condition == EquipmentCondition::GOOD;
}