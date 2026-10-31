#include <cassert>
#include <iostream>
#include <windows.h>

namespace {
    constexpr int INDEPENDENT_MIN = 0;
    constexpr int INDEPENDENT_MAX = 40;
    constexpr int QUIZ_MIN = 0;
    constexpr int QUIZ_MAX = 60;
    constexpr int CONTROL_RECORDS_LIMIT = 30;

    int calculateTotal(int independent, int quiz) {
        return independent + quiz;
    }

    const char* categoryFor(int independent, int m) {
        if (independent < 20) {
            return "потрібно посилити самостійну роботу";
        }
        if (m < 50) {
            return "підсумок нижче порога";
        }
        if (m <= 79) {
            return "стабільний результат";
        }
        return "високий результат";
    }

    bool isSearchMatch(int independent, int m) {
        return independent >= 20 && m >= 50;
    }

    bool readValidRecord(int recordNumber, int& independent, int& quiz) {
        while (true) {
            std::cout << "Запис " << recordNumber
                << " (independent 0..40, quiz 0..60): ";

            if (!(std::cin >> independent >> quiz)) {
                if (std::cin.eof()) {
                    std::cerr << "Неповне введення: досягнуто кінець вводу.\n";
                }
                else {
                    std::cerr << "Помилка формату: введіть два цілі числа. "
                        "Програму завершено без підсумку.\n";
                }
                return false;
            }

            if (independent < INDEPENDENT_MIN || independent > INDEPENDENT_MAX || quiz < QUIZ_MIN || quiz > QUIZ_MAX) {
                std::cerr << "Помилка діапазону. Повторіть увесь запис "
                    "(independent 0..40, quiz 0..60).\n";
                continue;
            }
            return true;
        }
    }
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    assert(calculateTotal(24, 48) == 72);
    assert(calculateTotal(15, 50) == 65);
    assert(isSearchMatch(24, 72));
    assert(!isSearchMatch(15, 65));

    int recordCount = 0;
    while (true) {
        std::cout << "Кількість записів N (1..30): ";
        if (!(std::cin >> recordCount)) {
            if (std::cin.eof()) {
                std::cerr << "Неповне введення N. Підсумок не формується.\n";
            }
            else {
                std::cerr << "Помилка формату N. Програму завершено.\n";
            }
            return 1;
        }
        if (recordCount >= 1 && recordCount <= CONTROL_RECORDS_LIMIT) {
            break;
        }
        std::cerr << "N має бути в межах 1..30. Введіть N ще раз.\n";
    }

    int sum = 0;
    int minimum = 0;
    int maximum = 0;
    int minimumRecord = 0;
    int maximumRecord = 0;
    int matchCount = 0;
    int firstMatch = 0;

    for (int acceptedRecord = 1; acceptedRecord <= recordCount; ++acceptedRecord) {
        int independent = 0;
        int quiz = 0;
        if (!readValidRecord(acceptedRecord, independent, quiz)) {
            return 1;
        }

        const int m = calculateTotal(independent, quiz);
        const bool matches = isSearchMatch(independent, m);

        if (acceptedRecord == 1) {
            sum = m;
            minimum = m;
            maximum = m;
            minimumRecord = acceptedRecord;
            maximumRecord = acceptedRecord;
        }
        else {
            sum += m;
            if (m < minimum) {
                minimum = m;
                minimumRecord = acceptedRecord;
            }
            if (m > maximum) {
                maximum = m;
                maximumRecord = acceptedRecord;
            }
        }

        if (matches) {
            ++matchCount;
            if (firstMatch == 0) {
                firstMatch = acceptedRecord;
            }
        }

        std::cout << "  m=" << m << " категорія: "
            << categoryFor(independent, m) << "; пошук: "
            << (matches ? "так" : "ні") << '\n';
    }

    const double average = static_cast<double>(sum) / recordCount;
    std::cout << "\nПІДСУМОК ПІСЛЯ " << recordCount << " ПРИЙНЯТИХ ЗАПИСІВ\n"
        << "Сума: " << sum << " \n"
        << "Середнє: " << average << " \n"
        << "Мінімум: " << minimum << " (запис " << minimumRecord << ")\n"
        << "Максимум: " << maximum << " (запис " << maximumRecord << ")\n"
        << "Кількість збігів: " << matchCount << '\n'
        << "Перший збіг: ";
    if (firstMatch == 0) {
        std::cout << "немає\n";
    }
    else {
        std::cout << firstMatch << '\n';
    }
    return 0;
}