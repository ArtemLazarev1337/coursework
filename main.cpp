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
#define KEY_ESCAPE 27

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

    std::cout << "Введите марку автомобиля: ";
    std::string carBrand;
    std::getline(std::cin, carBrand);
    record.carBrand = carBrand;

    std::cout << "Введите марку топлива: ";
    std::string fuelBrand;
    std::getline(std::cin, fuelBrand);
    record.fuelBrand = fuelBrand;

    std::cout << "Введите имя владельца: ";
    std::string ownerName;
    std::getline(std::cin, ownerName);
    record.ownerName = ownerName;

    std::cout << "Введите номер автомобиля: ";
    std::string carNumber;
    std::getline(std::cin, carNumber);
    record.carNumber = carNumber;

    std::cout << "Введите мощность двигателя: ";
    std::cin >> record.enginePower;

    std::cout << "Введите объём бака: ";
    std::cin >> record.tankCapacity;

    records.push_back(record);
}

void removeRecord(std::vector<Record> records) {
    int index;
    std::cout << "Введите индекс записи для удаления: ";
    std::cin >> index;
    if (index >= 0 && index < records.size()) records.erase(records.begin() + index);
    // std::system("clear");
    // std::cout << "\e[1mКакую запись вы бы хотели удалить?\e[0m\n";

    // bool isRunning = true;
    // int key;
    // while (isRunning) {
    //     key = getchar();
    //     switch (key) {
    //         case KEY_ARROW_UP:
    //             std::system("clear");
    //             //renderMenu();
    //             break;
    //         case KEY_ARROW_DOWN:
    //             std::system("clear");

    //             break;
    //     }
    // }
}

int main() {
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
                std::system("clear");
                selected = selected > 1 ? --selected : selected = OPTION_COUNT;
                break;
            case KEY_ARROW_DOWN:
                std::system("clear");
                selected = selected < 11 ? ++selected : selected = 1;
                break;
            case KEY_ENTER:
                std::system("clear");
                renderMenu(MENU, OPTION_COUNT, selected);

                switch (selected) {
                    case 1:  // Загрузка из файла
                        inputFromFile(records);
                        break;
                    case 2:  // Сохранение результатов обработки в файлах
                        outputToFile(records);
                        break;
                    case 3:  // Добавление записи
                        addRecord(records);
                        break;
                    case 4:  // Удаление записи
                        removeRecord(records);
                        break;
                    case 5:  // Вывод на экран дисплея данных и результатов обработки
                        printTable(records);
                        break;
                    case 6:  // Алфавитная сортировка по фамилии
                        customSort(records, compareByOwnerName);
                        break;
                    case 7:  // Сортировка по названию марки автомобиля, а при совпадении марки — по фамилии
                        customSort(records, compareByCarBrandAndOwnerName);
                        break;
                    case 8:  // Числовая сортировка по объему бака автомобиля
                        customSort(records, compareByTankCapacity);
                        break;
                    case 9:  // Перечень марок автомобилей с указанием их числа (результат отсортирован по названию марки автомобиля в алфавитном порядке)
                        printListOfBrands(records);
                        break;
                    case 10:  // Поиск по фамилии владельца (результат отсортирован по маркам в алфавитном порядке)
                        restoreBufferedInput();
                        std::cout << "Введите фамилию владельца автомобиля: ";
                        std::cin >> surname;
                        findByOwnerName(records, surname);
                        disableBufferedInput();
                        continue;
                    case 11:  // Завершить
                        isRunning = false;
                }
                continue;
            default:
                continue;
        }
        renderMenu(MENU, OPTION_COUNT, selected);
    }

    return 0;
}
