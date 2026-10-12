#include "models/transport/ElectricBicycle.h"

#include <stdexcept>
#include <utility>

ElectricBicycle::ElectricBicycle(
    std::string inventoryNumber,
    std::string name,
    std::string model,
    EquipmentCondition condition,
    int simplicity,
    double dailyEnergyKwh
)
    : Bicycle(
          std::move(inventoryNumber),
          std::move(name),
          std::move(model),
          condition,
          simplicity
      ),
      dailyEnergyKwh_(dailyEnergyKwh) {
    if (dailyEnergyKwh_ < 0) {
        throw std::invalid_argument(
            "Daily energy consumption cannot be negative"
        );
    }
}

double ElectricBicycle::getDailyEnergyKwh() const {
    return dailyEnergyKwh_;
}

std::string ElectricBicycle::getKind() const {
    return "Электровелосипед";
}
