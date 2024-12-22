#pragma once

#include "record.h"

void inputFromFile(std::vector<Record>& records, const std::string& fileName);

void outputToFile(std::vector<Record>& records, const std::string& fileName);
