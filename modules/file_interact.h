#pragma once

#include "record.h"

void inputFromFile(std::vector<Record>& records, const std::string& fileName);

void outputToFile(const std::vector<Record>& records, const std::string& fileName);
