#include "models/transport/ElectricScooter.h"

#include <stdexcept>
#include <utility>

ElectricScooter::ElectricScooter(
    std::string inventoryNumber,
    std::string name,
    std::string model,
    EquipmentCondition condition,
    int simplicity,
    double dailyEnergyKwh
)
    : Scooter(
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

double ElectricScooter::getDailyEnergyKwh() const {
    return dailyEnergyKwh_;
}

std::string ElectricScooter::getKind() const {
    return "Электросамокат";
}
