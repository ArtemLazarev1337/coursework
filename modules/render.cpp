#include <iostream>
#include <map>
#include <string>
#include <utility>
#include <vector>
#include "record.h"
#include "sorting.h"

std::string centerText(const std::string& text, int width) {
    int padding = width - text.size();
    if (padding <= 0) return text;
    int leftPadding = padding / 2;
    int rightPadding = padding - leftPadding;
    return std::string(leftPadding, ' ') + text + std::string(rightPadding, ' ');
}

void printTable(std::vector<Record>& records) {
    const int colWidths[] = {3, 10, 10, 5, 5, 15, 10};

    std::cout << "┌───┬──────────┬──────────┬─────┬─────┬───────────────┬──────────┐\n";
    for (int i = 0; i < records.size(); i++) {
        std::cout << "│\e[1m" << centerText(std::to_string(i + 1), colWidths[0]) << "\e[0m│"
                  << centerText(records[i].carBrand, colWidths[1]) << "│"
                  << centerText(records[i].fuelBrand, colWidths[2]) << "│"
                  << centerText(std::to_string(records[i].enginePower), colWidths[3]) << "│"
                  << centerText(std::to_string(records[i].tankCapacity), colWidths[4]) << "│"
                  << centerText(records[i].ownerName, colWidths[5]) << "│"
                  << centerText(records[i].carNumber, colWidths[6]) << "│\n";
        if (i < records.size() - 1)
            std::cout << "├───┼──────────┼──────────┼─────┼─────┼───────────────┼──────────┤\n";
    }
    std::cout << "└───┴──────────┴──────────┴─────┴─────┴───────────────┴──────────┘\n";
}

void printListOfBrands(const std::vector<Record>& records) {
    std::map<std::string, int> brandCounts;

    for (Record record : records) brandCounts[record.carBrand]++;

    const int colWidths[] = {4, 15, 7};

    unsigned int id = 1;
    std::cout << "┌────┬───────────────┬───────┐\n"
              << "│\e[1m" <<  centerText("ID", colWidths[0]) << "\e[0m│\e[1m"
              << centerText("Brand", colWidths[1]) << "\e[0m│\e[1m"
              << centerText("Count", colWidths[2]) << "\e[0m│\n"
              << "├────┼───────────────┼───────┤\n";;
    for (std::pair<std::string, int> pair : brandCounts) {
        std::cout << "│\e[1m" << centerText(std::to_string(id), colWidths[0]) << "\e[0m│"
                  << centerText(pair.first, colWidths[1]) << "│"
                  << centerText(std::to_string(pair.second), colWidths[2]) << "│\n";
        if (id < brandCounts.size())
            std::cout << "├────┼───────────────┼───────┤\n";
        id += 1;
    }
    std::cout << "└────┴───────────────┴───────┘\n";
    std::cout << "\e[1mВсего различных марок:\e[0m \e[33m" << brandCounts.size() << "\e[0m";
}

void findByOwnerName(const std::vector<Record>& records, const std::string& ownerSurname) {
    std::vector<Record> result;
    for (Record record : records) {
        std::string surname = record.ownerName.substr(0, record.ownerName.find(' '));
        if (ownerSurname == surname) result.push_back(record);
    }
    customSort(result, compareByCarBrandAndOwnerName);
    printTable(result);
}

void renderMenu(const std::string list[], int optionCount, int selectedOption) {
    for (int opt = 1; opt <= optionCount; opt++) {
        if (opt == selectedOption) std::cout << "\033[30;47m";
        std::cout << opt << ". " << list[opt - 1] << std::endl << "\033[0m";
    }
}
