#pragma once

#include <string>

#include "models/items/InventoryItem.h"

class SparePart : public InventoryItem {
public:
    SparePart(
        std::string inventoryNumber,
        std::string name,
        EquipmentCondition condition
    );

    std::string getKind() const override;
};