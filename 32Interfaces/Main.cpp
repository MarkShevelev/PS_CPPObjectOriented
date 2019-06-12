#include <iostream>
#include <string>

//Рассмотрим следующую задачу: написать программу с коммандным интерфейсом
//комманда exit - выход из программы
//комманды add mul и sub - запрашивают пару чисел и выводят сумму, произведение или разность, соответственно
//комманда div запрашивет два числа и либо печатает целую часть от деления, либо сообщает, что производится деление на ноль

//ранее мы бы решали эту задачу так:

void arithmetic() {
	bool proceed = true;
	while (proceed) {
		std::string command;
		std::cin >> command;

		if ("exit" == command) { proceed = false; continue; }
		if ("add" == command) {
			int a, b;
			std::cin >> a >> b;
			std::cout << (a + b) << std::endl;
			continue;
		}

		if ("mul" == command) {
			int a, b;
			std::cin >> a >> b;
			std::cout << (a * b) << std::endl;
			continue;
		}

		if ("sub" == command) {
			int a, b;
			std::cin >> a >> b;
			std::cout << (a - b) << std::endl;
			continue;
		}

		if ("div" == command) {
			int a, b;
			std::cin >> a >> b;
			if (0 == b) { std::cout << "Division by zero!" << std::endl; }
			else { std::cout << (a / b) << std::endl; }
			continue;
		}

		std::cout << "Unknown command" << std::endl;
	};
}

int main() {
	if (false) arithmetic();

	return 0;
}