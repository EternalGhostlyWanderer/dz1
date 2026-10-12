#include "app/AppContainer.h"

#include <stdexcept>
#include <string>
#include <utility>

#include "enums/EquipmentCondition.h"
#include "inspection/ServiceCenter.h"
#include "models/items/ChargingStation.h"
#include "models/items/DockingStation.h"
#include "models/items/Helmet.h"
#include "models/transport/Bicycle.h"
#include "models/transport/ElectricBicycle.h"
#include "models/transport/ElectricScooter.h"
#include "models/transport/Scooter.h"

namespace {

std::unique_ptr<InspectionService> requireService(
    std::unique_ptr<InspectionService> service
) {
    if (!service) {
        throw std::invalid_argument("Inspection service cannot be null");
    }

    return service;
}

EquipmentCondition readCondition(InputReader& input) {
    const int choice = input.readInt(
        "Состояние (1 - новое, 2 - хорошее, 3 - требует ремонта, "
        "4 - сломано, 5 - списано): "
    );

    switch (choice) {
        case 1:
            return EquipmentCondition::NEW;
        case 2:
            return EquipmentCondition::GOOD;
        case 3:
            return EquipmentCondition::NEEDS_REPAIR;
        case 4:
            return EquipmentCondition::BROKEN;
        case 5:
            return EquipmentCondition::RETIRED;
        default:
            throw std::invalid_argument("Condition must be from 1 to 5");
    }
}

// Данные, общие для всех объектов на балансе.
struct CommonInput {
    std::string inventoryNumber;
    std::string name;
    EquipmentCondition condition;
};

CommonInput readCommon(InputReader& input) {
    const std::string inventoryNumber = input.readString("Инвентарный номер: ");
    const std::string name = input.readString("Название: ");
    const EquipmentCondition condition = readCondition(input);

    return CommonInput{inventoryNumber, name, condition};
}

// Данные, общие для всего транспорта.
struct TransportInput {
    CommonInput common;
    std::string model;
    int simplicity;
};

TransportInput readTransport(InputReader& input) {
    const CommonInput common = readCommon(input);
    const std::string model = input.readString("Модель: ");
    const int simplicity = input.readInt("Простота для новичка (1-10): ");

    return TransportInput{common, model, simplicity};
}

}  // namespace

AppContainer::AppContainer()
    : AppContainer(std::make_unique<ServiceCenter>()) {}

AppContainer::AppContainer(std::unique_ptr<InspectionService> inspectionService)
    : inspectionService_(requireService(std::move(inspectionService))),
      parkService_(park_, *inspectionService_),
      parkReport_(park_),
      consoleApp_(
          parkService_,
          parkReport_,
          transportFactory_,
          itemFactory_,
          input_
      ) {}

void AppContainer::configure() {
    registerTransportTypes();
    registerItemTypes();
}

void AppContainer::run() {
    consoleApp_.run();
}

void AppContainer::registerTransportTypes() {
    transportFactory_.registerType("Самокат", [](InputReader& input) {
        const TransportInput data = readTransport(input);

        return std::make_unique<Scooter>(
            data.common.inventoryNumber,
            data.common.name,
            data.model,
            data.common.condition,
            data.simplicity
        );
    });

    transportFactory_.registerType("Велосипед", [](InputReader& input) {
        const TransportInput data = readTransport(input);

        return std::make_unique<Bicycle>(
            data.common.inventoryNumber,
            data.common.name,
            data.model,
            data.common.condition,
            data.simplicity
        );
    });

    transportFactory_.registerType("Электросамокат", [](InputReader& input) {
        const TransportInput data = readTransport(input);
        const double dailyEnergyKwh =
            input.readDouble("Расход энергии, кВт·ч в сутки: ");

        return std::make_unique<ElectricScooter>(
            data.common.inventoryNumber,
            data.common.name,
            data.model,
            data.common.condition,
            data.simplicity,
            dailyEnergyKwh
        );
    });

    transportFactory_.registerType("Электровелосипед", [](InputReader& input) {
        const TransportInput data = readTransport(input);
        const double dailyEnergyKwh =
            input.readDouble("Расход энергии, кВт·ч в сутки: ");

        return std::make_unique<ElectricBicycle>(
            data.common.inventoryNumber,
            data.common.name,
            data.model,
            data.common.condition,
            data.simplicity,
            dailyEnergyKwh
        );
    });
}

void AppContainer::registerItemTypes() {
    itemFactory_.registerType("Шлем", [](InputReader& input) {
        const CommonInput common = readCommon(input);
        const std::string size = input.readString("Размер: ");

        return std::make_unique<Helmet>(
            common.inventoryNumber, common.name, common.condition, size
        );
    });

    itemFactory_.registerType("Зарядная станция", [](InputReader& input) {
        const CommonInput common = readCommon(input);
        const double dailyEnergyKwh =
            input.readDouble("Расход энергии, кВт·ч в сутки: ");

        return std::make_unique<ChargingStation>(
            common.inventoryNumber,
            common.name,
            common.condition,
            dailyEnergyKwh
        );
    });

    itemFactory_.registerType("Док-станция", [](InputReader& input) {
        const CommonInput common = readCommon(input);

        return std::make_unique<DockingStation>(
            common.inventoryNumber, common.name, common.condition
        );
    });
}