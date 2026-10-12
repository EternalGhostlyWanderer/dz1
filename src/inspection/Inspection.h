#pragma once

#include "enums/InspectionResult.h"

class Inspection {
public:
    explicit Inspection(InspectionResult result);

    bool isPassed() const;

private:
    InspectionResult result_;
};