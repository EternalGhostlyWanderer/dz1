#pragma once

#include <string>

#include "models/Asset.h"

class Transport : public Asset {
public:
    Transport(
        std::string inventoryNumber,
        std::string name,
        std::string model,
        EquipmentCondition condition,
        int simplicity
    );

    std::string getModel() const;
    int getSimplicity() const;

protected:
    std::string model_;
    int simplicity_;
};
