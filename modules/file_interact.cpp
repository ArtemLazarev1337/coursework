#include <fstream>
#include <iostream>
#include <string>
#include "record.h"

void inputFromFile(std::vector<Record>& records, const std::string& fileName) {
    std::ifstream fin(fileName);

    if (!fin.is_open()) {
        std::cerr << "Не удалось открыть файл: " << fileName << std::endl;
        return;
    }

    records.clear();

    Record record;
    while (fin >> record.carBrand >> record.fuelBrand >> record.enginePower >>
                 record.tankCapacity) {
        std::string surname, initials;
        fin >> surname >> initials;
        record.ownerName = surname + " " + initials;

        fin >> record.carNumber;
        records.push_back(record);
    }

    fin.close();
}

void outputToFile(std::vector<Record>& records, const std::string& fileName) {
    std::ofstream fout(fileName);

    for (Record record : records) {
        fout << record.carBrand << " ";
        fout << record.fuelBrand << " ";
        fout << record.enginePower << " ";
        fout << record.tankCapacity << " ";
        fout << record.ownerName << " ";
        fout << record.carNumber << " ";
    }
}
