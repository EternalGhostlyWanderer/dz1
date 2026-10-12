#include "models/items/ChargingStation.h"

#include <stdexcept>
#include <utility>

ChargingStation::ChargingStation(
    std::string inventoryNumber,
    std::string name,
    EquipmentCondition condition,
    double dailyEnergyKwh
)
    : InventoryItem(
          std::move(inventoryNumber),
          std::move(name),
          condition
      ),
      dailyEnergyKwh_(dailyEnergyKwh) {
    if (dailyEnergyKwh_ < 0) {
        throw std::invalid_argument(
            "Daily energy consumption cannot be negative"
        );
    }
}

double ChargingStation::getDailyEnergyKwh() const {
    return dailyEnergyKwh_;
}

std::string ChargingStation::getKind() const {
    return "Зарядная станция";
}