#include "models/transport/Scooter.h"

#include <utility>

Scooter::Scooter(
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

std::string Scooter::getKind() const {
    return "Самокат";
}
