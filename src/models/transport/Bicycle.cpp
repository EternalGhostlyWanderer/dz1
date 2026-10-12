#include "models/transport/Bicycle.h"

#include <utility>

Bicycle::Bicycle(
    std::string inventoryNumber,
    std::string name,
    std::string model,
    EquipmentCondition condition,
    int simplicity
)
    : Transport(
          std::move(inventoryNumber),
          std::move(name),
          std::move(model),
          condition,
          simplicity
      ) {}

std::string Bicycle::getKind() const {
    return "Велосипед";
}
