#include <iostream>
#include <windows.h>

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int independent = 0;
	int quiz = 0;
	int total = independent + quiz;
	using namespace std;

	if (!(std::cin >> independent >> quiz)) {
		std::cerr << "Помилка: введіть цілі значення балів\n";
		return 1;
	}
	if (independent < 0 || independent > 40 || quiz < 0 || quiz > 60) {
		std::cerr << "Помилка: значення поза допустимими межами\n";
		return 1;
	}

	if (independent < 20) {
		std::cout << "потрібно посилити самостійну роботу";
	}
	else if (total < 50) {
		std::cout << "підсумок нижче порога";
	}
	else if (total <= 79) {
		std::cout << "стабільний результат";
	}
	else if (total >= 80) {
		std::cout << "високий результат";
	}

    return 0;
}
