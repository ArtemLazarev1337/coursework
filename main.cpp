#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include "modules/record.h"
#include "modules/termfix.h"
#include "modules/file_interact.h"
#include "modules/render.h"
#include "modules/sorting.h"

#define KEY_ARROW_UP 65
#define KEY_ARROW_DOWN 66
#define KEY_ENTER 10
#define KEY_BACKSPACE 127
#define KEY_1 49
#define KEY_2 50
#define KEY_3 51
#define KEY_4 52
#define KEY_5 53
#define KEY_6 54
#define KEY_7 55
#define KEY_8 56
#define KEY_9 57

std::vector<Record> records;

const std::string MENU[] = {
    "Загрузка из файла",
    "Сохранение результатов обработки в файлах",
    "Добавление записи",
    "Удаление записи",
    "Вывод на экран дисплея данных и результатов обработки",
    "Алфавитная сортировка по фамилии",
    "Сортировка по названию марки автомобиля, а при совпадении марки — по фамилии",
    "Числовая сортировка по объему бака автомобиля",
    "Перечень марок автомобилей с указанием их числа (результат отсортирован по названию марки автомобиля в алфавитном порядке)",
    "Поиск по фамилии владельца (результат отсортирован по маркам в алфавитном порядке)",
    "Завершить"
};
const int OPTION_COUNT = sizeof(MENU) / sizeof(MENU[0]);

void addRecord(std::vector<Record>& records) {
    Record record;

    std::cout << "\033[1mВведите марку автомобиля: \033[0m";
    std::string carBrand;
    std::getline(std::cin, carBrand);
    record.carBrand = carBrand;

    std::cout << "\033[1mВведите марку топлива: \033[0m";
    std::string fuelBrand;
    std::getline(std::cin, fuelBrand);
    record.fuelBrand = fuelBrand;

    std::cout << "\033[1mВведите имя владельца: \033[0m";
    std::string ownerName;
    std::getline(std::cin, ownerName);
    record.ownerName = ownerName;

    std::cout << "\033[1mВведите номер автомобиля: \033[0m";
    std::string carNumber;
    std::getline(std::cin, carNumber);
    record.carNumber = carNumber;

    std::cout << "\033[1mВведите мощность двигателя (число): \033[0m";
    std::cin >> record.enginePower;

    std::cout << "\033[1mВведите объём бака (число): \033[0m";
    std::cin >> record.tankCapacity;

    records.push_back(record);

    std::cout << "\033[0;32mЗапись добавлена!\033[0m";
}

void removeRecord(std::vector<Record>& records) {
    if (records.empty()) {
        std::cout << "Нет записей для удаления!" << std::endl;
        return;
    }

    unsigned int selected = 1;

    bool isRunning = true;

    int key;
    while (isRunning) {
        std::system("clear");

        const int colWidths[] = {4, 15, 12, 14, 15, 16, 12};
        std::cout << "┌────┬───────────────┬────────────┬──────────────┬───────────────┬────────────────┬────────────┐\n"
                  << "│\e[1m" << centerText("ID", colWidths[0]) << "\e[0m│\e[1m"
                  << centerText("Brand", colWidths[1]) << "\e[0m│\e[1m"
                  << centerText("Fuel Brand", colWidths[2]) << "\e[0m│\e[1m"
                  << centerText("Engine Power", colWidths[3]) << "\e[0m│\e[1m"
                  << centerText("Tank Capacity", colWidths[4]) << "\e[0m│\e[1m"
                  << centerText("Owner Name", colWidths[5]) << "\e[0m│\e[1m"
                  << centerText("Car Number", colWidths[6]) << "\e[0m│\n"
                  << "├────┼───────────────┼────────────┼──────────────┼───────────────┼────────────────┼────────────┤\n";
        for (int i = 0; i < records.size(); i++) {
            std::cout << "│\e[1m" << centerText(selected == i + 1 ? " \xE2\x9D\x8C " : std::to_string(i + 1), colWidths[0]) << "\e[0m│"
                      << centerText(records[i].carBrand, colWidths[1]) << "│"
                      << centerText(records[i].fuelBrand, colWidths[2]) << "│"
                      << centerText(std::to_string(records[i].enginePower), colWidths[3]) << "│"
                      << centerText(std::to_string(records[i].tankCapacity), colWidths[4]) << "│"
                      << centerText(records[i].ownerName, colWidths[5]) << "│"
                      << centerText(records[i].carNumber, colWidths[6]) << "│\n";
            if (i < records.size() - 1)
                std::cout << "├────┼───────────────┼────────────┼──────────────┼───────────────┼────────────────┼────────────┤\n";
        }
        std::cout << "└────┴───────────────┴────────────┴──────────────┴───────────────┴────────────────┴────────────┘\n";

        key = getchar();
        switch (key) {
            case KEY_ARROW_UP:
                selected = (selected > 1) ? (selected - 1) : records.size();
                break;
            case KEY_ARROW_DOWN:
                selected = (selected < records.size()) ? (selected + 1) : 1;
                break;
            case KEY_ENTER:
                records.erase(records.begin() + (selected - 1));
                if (records.empty()) {
                    isRunning = false;
                } else {
                    selected = (selected > records.size()) ? records.size() : selected;
                }
                break;
            case KEY_BACKSPACE:
                isRunning = false; // Выход
                break;
        }
    }
}

int main() {
    unsigned int sortType;
    std::string fileInput;
    std::string fileOutput;
    std::string surname;

    std::system("clear");

    disableBufferedInput();

    int selected = 1;
    renderMenu(MENU, OPTION_COUNT, selected);

    bool isRunning = true;

    int key;
    while (isRunning) {
        key = getchar();
        switch (key) {
            case KEY_ARROW_UP:
                selected = selected > 1 ? --selected : selected = OPTION_COUNT;
                std::system("clear");
                renderMenu(MENU, OPTION_COUNT, selected);
                break;
            case KEY_ARROW_DOWN:
                selected = selected < OPTION_COUNT ? ++selected : selected -= (OPTION_COUNT - 1);
                std::system("clear");
                renderMenu(MENU, OPTION_COUNT, selected);
                break;
            case KEY_ENTER:
                std::system("clear");
                renderMenu(MENU, OPTION_COUNT, selected);
                switch (selected) {
                    case 1:  // Загрузка из файла
                        restoreBufferedInput();
                        std::cout << "\033[1mВведите имя файла для загрузки: \033[0m";
                        std::cin >> fileInput;
                        std::cin.ignore();
                        inputFromFile(records, fileInput);
                        disableBufferedInput();
                        break;
                    case 2:  // Сохранение результатов обработки в файлах
                        restoreBufferedInput();
                        std::cout << "\033[1mВведите имя файла для сохранения: \033[0m";
                        std::cin >> fileOutput;
                        std::cin.ignore();
                        outputToFile(records, fileOutput);
                        disableBufferedInput();
                        break;
                    case 3:  // Добавление записи
                        restoreBufferedInput();
                        addRecord(records);
                        std::cin.ignore();
                        disableBufferedInput();
                        break;
                    case 4:  // Удаление записи
                        removeRecord(records);
                        break;
                    case 5:  // Вывод на экран дисплея данных и результатов обработки
                        printTable(records);
                        break;
                    case 6:  // Алфавитная сортировка по фамилии
                        restoreBufferedInput();
                        std::cout << "\033[1m1. По возрастанию/2. По убыванию: \033[0m";
                        std::cin >> sortType;
                        std::cin.ignore();
                        if (sortType == 1) {
                            customSort(records, compareByOwnerName, true);
                            std::cout << "\033[32mДанные успешно отсортированы!\033[0m\n";
                        } else if (sortType == 2) {
                            customSort(records, compareByOwnerName, false);
                            std::cout << "\033[32mДанные успешно отсортированы!\033[0m\n";
                        } else {
                            std::cout << "\033[31mТакого варианта нет!\033[0m";
                        }
                        disableBufferedInput();
                        break;
                    case 7:  // Сортировка по названию марки автомобиля, а при совпадении марки — по фамилии
                        restoreBufferedInput();
                        std::cout << "\033[1m1. По возрастанию/2. По убыванию: \033[0m";
                        std::cin >> sortType;
                        std::cin.ignore();
                        if (sortType == 1) {
                            customSort(records, compareByCarBrandAndOwnerName, true);
                            std::cout << "\033[32mДанные успешно отсортированы!\033[0m\n";
                        } else if (sortType == 2) {
                            customSort(records, compareByCarBrandAndOwnerName, false);
                            std::cout << "\033[32mДанные успешно отсортированы!\033[0m\n";
                        } else {
                            std::cout << "\033[31mТакого варианта нет!\033[0m";
                        }
                        disableBufferedInput();
                        break;
                    case 8:  // Числовая сортировка по объему бака автомобиля
                        restoreBufferedInput();
                        std::cout << "\033[1m1. По возрастанию/2. По убыванию: \033[0m";
                        std::cin >> sortType;
                        std::cin.ignore();
                        if (sortType == 1) {
                            customSort(records, compareByTankCapacity, true);
                            std::cout << "\033[32mДанные успешно отсортированы!\033[0m\n";
                        } else if (sortType == 2) {
                            customSort(records, compareByTankCapacity, false);
                            std::cout << "\033[32mДанные успешно отсортированы!\033[0m\n";
                        } else {
                            std::cout << "\033[31mТакого варианта нет!\033[0m";
                        }
                        disableBufferedInput();
                        break;
                    case 9:  // Перечень марок автомобилей с указанием их числа (результат отсортирован по названию марки автомобиля в алфавитном порядке)
                        printListOfBrands(records);
                        break;
                    case 10:  // Поиск по фамилии владельца (результат отсортирован по маркам в алфавитном порядке)
                        restoreBufferedInput();
                        std::cout << "\033[1mВведите фамилию владельца автомобиля: \033[0m";
                        std::cin >> surname;
                        std::cin.ignore();
                        findByOwnerName(records, surname);
                        disableBufferedInput();
                        break;
                    case 11:  // Завершить
                        isRunning = false;
                        break;
                }
                break;
            case KEY_BACKSPACE:
                std::system("clear");
                renderMenu(MENU, OPTION_COUNT, selected);
                break;
            case KEY_1:
            case KEY_2:
            case KEY_3:
            case KEY_4:
            case KEY_5:
            case KEY_6:
            case KEY_7:
            case KEY_8:
            case KEY_9:
                selected = key - 48;
                std::system("clear");
                renderMenu(MENU, OPTION_COUNT, selected);
                break;
        }
    }

    return 0;
}
