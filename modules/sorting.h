#pragma once

#include <vector>
#include "record.h"

void customSort(std::vector<Record>& records, bool (*compare)(const Record&, const Record&));

bool compareByOwnerName(const Record& a, const Record& b);

bool compareByCarBrandAndOwnerName(const Record& a, const Record& b);

bool compareByTankCapacity(const Record& a, const Record& b);
