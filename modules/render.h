#pragma once

#include <string>
#include "record.h"

std::string centerText(const std::string& text, int width);
void printTable(std::vector<Record>& records);
void printListOfBrands(const std::vector<Record>& records);
void findByOwnerName(const std::vector<Record>& records, const std::string& ownerSurname);
void renderMenu(const std::string list[], int optionCount, int selectedOption);
