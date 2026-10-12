#include "models/items/SparePart.h"

#include <utility>

SparePart::SparePart(
    std::string inventoryNumber,
    std::string name,
    EquipmentCondition condition
)
    : InventoryItem(
          std::move(inventoryNumber),
          std::move(name),
          condition
      ) {}

std::string SparePart::getKind() const {
    return "Запчасть";
}