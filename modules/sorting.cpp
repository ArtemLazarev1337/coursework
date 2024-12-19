#include <vector>
#include "record.h"

void swap(Record& a, Record& b) {
    Record t = a;
    a = b;
    b = t;
}

void customSort(std::vector<Record>& records, bool (*compare)(const Record&, const Record&)) {
    for (int i = 0; i < records.size() - 1; i++) {
        for (int j = i + 1; j < records.size(); j++) {
            if (compare(records[i], records[j])) {
                swap(records[i], records[j]);
            }
        }
    }
}

bool compareByOwnerName(const Record& a, const Record& b) {
    return a.ownerName > b.ownerName;
}

bool compareByCarBrandAndOwnerName(const Record& a, const Record& b) {
    if (a.carBrand == b.carBrand) return a.ownerName > b.ownerName;
    return a.carBrand > b.carBrand;
}

bool compareByTankCapacity(const Record& a, const Record& b) {
    return a.tankCapacity > b.tankCapacity;
}
