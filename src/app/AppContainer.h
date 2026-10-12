#pragma once

#include <memory>

#include "app/ConsoleApp.h"
#include "factory/ItemFactory.h"
#include "factory/TransportFactory.h"
#include "interfaces/InspectionService.h"
#include "park/Park.h"
#include "park/ParkReport.h"
#include "park/ParkService.h"
#include "reader/ConsoleInputReader.h"

// Composition root: единственное место, где создаются объекты и
// связываются зависимости.
class AppContainer {
public:
    // Рабочая конфигурация: настоящий ServiceCenter.
    AppContainer();

    // Подмена техосмотра (в тестах - заглушка).
    explicit AppContainer(std::unique_ptr<InspectionService> inspectionService);

    AppContainer(const AppContainer&) = delete;
    AppContainer& operator=(const AppContainer&) = delete;

    // Регистрирует виды транспорта и вещей в фабриках.
    void configure();

    void run();

private:
    // Порядок полей важен: зависимости объявлены раньше потребителей.
    Park park_;
    std::unique_ptr<InspectionService> inspectionService_;
    ParkService parkService_;
    ParkReport parkReport_;
    TransportFactory transportFactory_;
    ItemFactory itemFactory_;
    ConsoleInputReader input_;
    ConsoleApp consoleApp_;

    void registerTransportTypes();
    void registerItemTypes();
};