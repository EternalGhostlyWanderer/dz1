#include "models/transport/Transport.h"

#include <stdexcept>
#include <utility>

Transport::Transport(
    std::string inventoryNumber,
    std::string name,
    std::string model,
    EquipmentCondition condition,
    int simplicity
)
    : Asset(
          std::move(inventoryNumber),
          std::move(name),
          condition
      ),
      model_(std::move(model)),
      simplicity_(simplicity) {
    if (model_.empty()) {
        throw std::invalid_argument("Model cannot be empty");
    }

    if (simplicity_ < 1 || simplicity_ > 10) {
        throw std::invalid_argument("Simplicity must be from 1 to 10");
    }
}

std::string Transport::getModel() const {
    return model_;
}

int Transport::getSimplicity() const {
    return simplicity_;
}
