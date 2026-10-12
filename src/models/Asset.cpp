#include "models/Asset.h"

#include <stdexcept>
#include <utility>

Asset::Asset(
    std::string inventoryNumber,
    std::string name,
    EquipmentCondition condition
)
    : inventoryNumber_(std::move(inventoryNumber)),
      name_(std::move(name)),
      condition_(condition) {
    if (inventoryNumber_.empty()) {
        throw std::invalid_argument("Inventory number cannot be empty");
    }

    if (name_.empty()) {
        throw std::invalid_argument("Name cannot be empty");
    }
}

std::string Asset::getInventoryNumber() const {
    return inventoryNumber_;
}

std::string Asset::getName() const {
    return name_;
}

EquipmentCondition Asset::getCondition() const {
    return condition_;
}
