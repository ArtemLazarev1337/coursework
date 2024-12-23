#pragma once

#include <vector>
#include "record.h"

void customSort(std::vector<Record>& records, bool (*compare)(const Record&, const Record&, bool ascending), bool ascending = true);

bool compareByOwnerName(const Record& a, const Record& b, bool ascending);

bool compareByCarBrandAndOwnerName(const Record& a, const Record& b, bool ascending);

bool compareByTankCapacity(const Record& a, const Record& b, bool ascending);
