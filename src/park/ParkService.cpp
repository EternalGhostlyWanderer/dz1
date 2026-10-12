#include "park/ParkService.h"

#include <stdexcept>
#include <utility>

ParkService::ParkService(Park& park, InspectionService& inspectionService)
    : park_(park), inspectionService_(inspectionService) {}

Inspection ParkService::accept(std::unique_ptr<Inventoriable> item) {
    if (!item) {
        throw std::invalid_argument("Item cannot be null");
    }

    if (park_.findByInventoryNumber(item->getInventoryNumber()) != nullptr) {
        throw std::invalid_argument(
            "Inventory number is already in the park: " +
            item->getInventoryNumber()
        );
    }

    const Inspection inspection = inspectionService_.inspect(*item);

    if (inspection.isPassed()) {
        park_.addItem(std::move(item));
    }

    return inspection;
}

bool ParkService::removeItem(const std::string& number) {
    return park_.removeByInventoryNumber(number);
}