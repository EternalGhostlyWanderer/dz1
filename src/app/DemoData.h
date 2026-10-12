#pragma once

#include <memory>
#include <vector>

#include "models/Asset.h"

// Набор объектов для демонстрационного сценария: есть и те, что пройдут
// техосмотр, и те, что не пройдут, и повтор инвентарного номера.
std::vector<std::unique_ptr<Asset>> makeDemoAssets();