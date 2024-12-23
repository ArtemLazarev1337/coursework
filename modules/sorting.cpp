#include <vector>
#include "record.h"

void swap(Record& a, Record& b) {
    Record t = a;
    a = b;
    b = t;
}

void customSort(std::vector<Record>& records, bool (*compare)(const Record&, const Record&, bool ascending), bool ascending = true) {
    bool isSorted = false;
    while (!isSorted) {
        isSorted = true;
        for (int i = 1; i < records.size(); i++) {
            if (compare(records[i - 1], records[i], ascending)) {
                swap(records[i - 1], records[i]);
                isSorted = false;
            }
        }
    }
}

bool compareByOwnerName(const Record& a, const Record& b, bool ascending) {
    return ascending ? a.ownerName > b.ownerName : a.ownerName < b.ownerName;
}

bool compareByCarBrandAndOwnerName(const Record& a, const Record& b, bool ascending) {
    if (a.carBrand == b.carBrand) return ascending ? a.ownerName > b.ownerName : a.ownerName < b.ownerName;
    return ascending ? a.carBrand > b.carBrand : a.carBrand < b.carBrand;
}

bool compareByTankCapacity(const Record& a, const Record& b, bool ascending) {
    return ascending ? a.tankCapacity > b.tankCapacity : a.tankCapacity < b.tankCapacity;
}
