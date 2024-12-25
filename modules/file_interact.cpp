#include <fstream>
#include <iostream>
#include <string>
#include "record.h"

void inputFromFile(std::vector<Record>& records, const std::string& fileName) {
    std::ifstream fin(fileName);

    if (!fin.is_open()) {
        std::cerr << "\033[31mНе удалось открыть файл: \033[0;33m" << fileName << "\033[0m\n";
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

    std::cout << "\033[32mДанные успешно загружены!\033[0m";
}

void outputToFile(const std::vector<Record>& records, const std::string& fileName) {
    std::ofstream fout(fileName);

    for (Record record : records) {
        fout << record.carBrand << " ";
        fout << record.fuelBrand << " ";
        fout << record.enginePower << " ";
        fout << record.tankCapacity << " ";
        fout << record.ownerName << " ";
        fout << record.carNumber << " ";
        fout << "\n";
    }

    std::cout << "\033[32mДанные успешно сохранены!\033[0m";
}
