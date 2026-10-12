#include "inspection/Inspection.h"

Inspection::Inspection(InspectionResult result) : result_(result) {}

bool Inspection::isPassed() const {
    return result_ == InspectionResult::PASSED;
}