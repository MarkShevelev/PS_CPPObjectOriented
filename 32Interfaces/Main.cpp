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

//Понятно, что можно было бы заменить многократные if на поиск в словаре
//Однако не ясно, что именно должно быть элементом словаря
//На каждое слово мы производим какой-то код
//В решении этой задачи нам поможет полиморфизм!

//создадим базовый класс
struct CommandProcess {
	virtual bool process() const { return true; } //метод процесс возвращает нам proceed, флаг продолжения
	//метод виртуальный, потому что мы собираемся дать ему другие реализации в выденных классах
};

struct Exit : CommandProcess {
	bool process() const { return false; } //команда Exit изменяет метод так, что он всегда возвращает false, т.е. прерывает работу мгновенно
};

struct Add : CommandProcess {
	bool process() const {
		int a, b;
		std::cin >> a >> b;
		std::cout << (a + b) << std::endl;
		return true;
	}
};

//реорганизуем основную функцию
#include <map>
void arithmetic_polymorphic() {
	std::map <std::string, CommandProcess*> commands;
	Exit exit;
	Add add;
	commands["exit"] = &exit;
	commands["add"] = &add;

	bool proceed = true;
	while (proceed) {
		std::string command;
		std::cin >> command;

		auto process_it = commands.find(command); //ищем объект с кодом, который необходимо выполнить
		//если не находим, то выполняем код для ошибочной команды
		if (commands.end() == process_it) { std::cout << "Unknown command" << std::endl; continue; }

		//в остальных случаях делегируем работу найденной команде
		proceed = process_it->second->process(); 
	}
}

int main() {
	if (false) arithmetic();
	if (false) arithmetic_polymorphic();

	return 0;
}