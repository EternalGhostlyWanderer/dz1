#include "app/DemoData.h"

#include "models/items/ChargingStation.h"
#include "models/items/DockingStation.h"
#include "models/items/Helmet.h"
#include "models/transport/Bicycle.h"
#include "models/transport/ElectricBicycle.h"
#include "models/transport/ElectricScooter.h"
#include "models/transport/Scooter.h"

std::vector<std::unique_ptr<Asset>> makeDemoAssets() {
    std::vector<std::unique_ptr<Asset>> assets;

    // Пройдут техосмотр.
    assets.push_back(std::make_unique<Scooter>(
        "SC-001", "Городской самокат", "Kugoo S1",
        EquipmentCondition::NEW, 9));
    assets.push_back(std::make_unique<ElectricScooter>(
        "ES-001", "Электросамокат", "Xiaomi Mi 3",
        EquipmentCondition::GOOD, 8, 0.6));
    assets.push_back(std::make_unique<Bicycle>(
        "BC-001", "Горный велосипед", "Stels Navigator",
        EquipmentCondition::GOOD, 4));
    assets.push_back(std::make_unique<ElectricBicycle>(
        "EB-001", "Электровелосипед", "Eltreco Ultra",
        EquipmentCondition::NEW, 5, 1.2));
    assets.push_back(std::make_unique<Helmet>(
        "HM-001", "Шлем взрослый", EquipmentCondition::GOOD, "M"));
    assets.push_back(std::make_unique<ChargingStation>(
        "CS-001", "Зарядная станция", EquipmentCondition::GOOD, 3.5));
    assets.push_back(std::make_unique<DockingStation>(
        "DS-001", "Док-станция", EquipmentCondition::NEW));

    // Не пройдут техосмотр.
    assets.push_back(std::make_unique<ElectricBicycle>(
        "EB-002", "Электровелосипед", "Eltreco Ultra",
        EquipmentCondition::BROKEN, 5, 1.2));
    assets.push_back(std::make_unique<Helmet>(
        "HM-002", "Шлем детский", EquipmentCondition::RETIRED, "S"));

    // Повтор инвентарного номера: объект будет отклонён до техосмотра.
    assets.push_back(std::make_unique<Scooter>(
        "SC-001", "Городской самокат", "Kugoo S1",
        EquipmentCondition::NEW, 9));

    return assets;
}