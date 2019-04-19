#include <iostream>

//в некоторых ситуациях нам может потребоваться обратное преобразование
//т.е. какой-то объект неявно преобразовать в примитивный тип языка C++, например, в int
//в этом помогут операторы преобразования типа

class Counter {
	int counter;
public:
	Counter(int begin) {
		counter = begin;
	}

	int next() {
		return counter++;
	}

	//синтаксис объявления оператор преобразования типа
	operator int() {
		return counter;
	}
};

void print_int(int i) {
	std::cout << i << std::endl;
}

void print_int_test() {
	Counter c(10);
	print_int(c);
}

//при необходимости операторы преобразования типов, как и конструкторы, могут быть объявлены explicit
class IsPositive {
	int x;
public:
	IsPositive(int x) {
		IsPositive::x = x;
	}

	explicit operator bool() {
		return x > 0;
	}
};

void print_bool(bool b) {
	std::cout << std::boolalpha << b << std::endl;
}

void print_bool_test() {
	IsPositive neg(-1);
	//print_bool(neg); //не работает, т.к. преобразование объявлено explicit (явное)
	//однако по-прежнему можно выполнить явное преобразование
	//его можно выполнить тремя способами
	print_bool((bool)neg); //C-style - способ из языка Си
	print_bool(bool(neg)); //С++ - style - способ вызова конструктора
	print_bool(static_cast<bool>(neg)); //вызов конструкции преобразования типа
}

//в частности такой подход можно использовать со стандартными потоками ввода/вывода
void std_cin_test() {
	int i;
	std::cin >> i;
	if (!std::cin) { //здесь мы используем тот факт, что std::cin приводится к типу bool: true - поток в нормальном состоянии, false - ошибка
		std::cout << "Not a number!" << std::endl;
	}
}

int main() {
	if (false) print_int_test();
	if (false) print_bool_test();
	if (false) std_cin_test();
}