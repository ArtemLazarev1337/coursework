#include <cstdlib>
#include <iostream>
#include <termios.h>
#include <unistd.h>
#include <string>
#include "record.h"

#define KEY_ARROW_UP 65
#define KEY_ARROW_DOWN 66
#define KEY_ENTER 10

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

void disableBufferedInput() {
    struct termios t;
    tcgetattr(STDIN_FILENO, &t);          // Получаем текущие настройки терминала
    t.c_lflag &= ~ICANON;                 // Отключаем канонический режим
    t.c_lflag &= ~ECHO;                   // Отключаем эхо-ввод
    tcsetattr(STDIN_FILENO, TCSANOW, &t); // Применяем изменения
}

void renderMenu(int selectedOption) {
    for (int opt = 1; opt <= OPTION_COUNT; opt++) {
        if (opt == selectedOption) std::cout << "\033[30;47m";
        std::cout << opt << ". " << MENU[opt - 1] << std::endl << "\033[0m";
    }
}

int main() {
    disableBufferedInput();

    int selected = 1;
    renderMenu(selected);

    bool isRunning = true;
    int key;
    while (isRunning) {
        key = getchar();
        switch (key) {
            case KEY_ARROW_UP:
                std::system("clear");
                selected = selected > 1 ? --selected : selected = 11;
                break;
            case KEY_ARROW_DOWN:
                std::system("clear");
                selected = selected < 11 ? ++selected : selected = 1;
                break;
            case KEY_ENTER:
                std::system("clear");
                renderMenu(selected);

                switch (selected) {
                    case 1:
                        std::cout << "test";
                        break;
                    case 11:
                        return 0;
                }
                continue;
            default:
                continue;
        }
        renderMenu(selected);
    }

    return 0;
}
