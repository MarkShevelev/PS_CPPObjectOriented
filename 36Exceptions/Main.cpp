#include <iostream>
#include <string>

//В некоторых случаях нам приходится сталкиваться с проблемой корректного возвращаемого значения
//Рассмотрим класс Stack

class Stack {
public:
	Stack(size_t max_size) : max_size(max_size), top(0) {
		data_ptr =  new (std::nothrow) int[max_size];
	}

	void push(int x) { 
		data_ptr[top++] = x;
	}

	int pop() {
		return data_ptr[--top];
	}

	bool empty() const { return 0 == top; }

private:
	size_t max_size, top;
	int *data_ptr;
};

//Проблема использования класса Stack состоит в том, что несколько методов могут оказаться в ситуации невозможности выполнить требуемое
//например метод push может столкнуться с переполненным стеком
//мы могли бы сделать проверки, но как сообщить пользователю об ошибке?
//например вернуть значение типа bool, которое обозначит верное исполнение
class CheckStack {
public:
	CheckStack(size_t max_size) : max_size(max_size), top(0) {
		data_ptr = new (std::nothrow) int[max_size];
	}

	bool push(int x) {
		if (top == max_size) return false;
		data_ptr[top++] = x;
		return true;
	}

	bool pop(int &x) { //такой подход неудачно сказывается на методе pop :(
		if (0 == top) return false;
		x = data_ptr[--top];
		return true;
	}

	bool empty() const { return 0 == top; }

private:
	size_t max_size, top;
	int *data_ptr;
};
//Использование флага в возвращаемом значении неудобно для метода pop, т.к. мы не можем вернуть значение нормально из функции, а вынуждены его записывать по ссылке
//не говоря уже о том, что мы будем вынуждены тащить через каждый вызов операций над стеком проверки корректности

bool add_numbers_to_stack(int *range_begin, int *range_end, CheckStack &st) {
	for (int *it = range_begin; it != range_end; ++it)
		if (st.push(*it)) return false; //приходится производить проверки
	return true; //и возвращать булевое значение при каждом использовании стека
}

//помимо неудобств есть проблема конструктора
//если в конструкторе не удастся выделить память, то как мы можем сообщить о поломке?

//Для со сложностью в обработке ошибок многие ООП языки программирования используют механизм "Исключений"
//Исключения - это механизм аварийного завершения работы функции или метода в ситуации, когда она не может удовлетворить контракту, например, вернуть значение

//рассмотрим функцию деления
int divv(int x, int y) {
	return x / y;
}

//такая функция обладает недостатком: она не может вернуть верного значения, если y == 0
//Если мы обнаружили такую ситуацию, то должны сразу прервать работу функции, не дав возможности дойти до опасного участка кода
int return_divv(int x, int y) {
	if (0 == y) return 0; //Но что мы должны вернуть? как пользователь узнает, что произошла ошибка?
	return x / y;
}
//подход с return не даст желаемого, т.к. программист, который использует нашу функцию, не сможет отличить нормальный нулевой результат от ошибки деления на ноль
//здесь нам и помогут исключения!

int exception_divv(int x, int y) {
	if (0 == y) throw 0; //ключевое слово throw приводит к прерыванию работы функции
	return x / y;
}

void exception_divv_test() {
	int x, y;
	std::cin >> x >> y;
	std::cout << exception_divv(x, y) << std::endl;
}

//при использовании throw говорят, что было выброшено исключение
//в языке C++ исключение - это любое значение, примитивного типа или объект любого класса
//Например можно выбросить строку
//перепишем Stack через выбрасывание строковых исключений

class ExceptionStack {
public:
	ExceptionStack(size_t max_size) : max_size(max_size), top(0) {
		data_ptr = new (std::nothrow) int[max_size];
		if (nullptr == data_ptr) throw std::string("Not enough memory!");
	}

	void push(int x) {
		if (top == max_size) throw std::string("Stack overflow!");
		data_ptr[top++] = x;
	}

	int pop() {
		if (0 == top) throw std::string("Pop from an empty stack!");
		return data_ptr[--top];
	}

	bool empty() const { return 0 == top; }

private:
	size_t max_size, top;
	int *data_ptr;
};

void exceptional_stack_test() {
	std::cout
		<< "1) Normal stack work\n"
		<< "2) Stack overflow\n"
		<< "3) Pop from an empry stack\n"
		<< std::endl;

	int i;
	std::cin >> i;
	ExceptionStack est(5);
	switch (i) {
	case 2: {
		est.push(-1); est.push(-1);
	}
	case 3: {
		std::cout << est.pop() << std::endl;
	}
	case 1: {
		for (int cnt = 0; cnt != 5; ++cnt)
			est.push(cnt);
		for (int cnt = 0; cnt != 5; ++cnt)
			std::cout << est.pop() << ' ';
		std::cout << std::endl;
		std::cout << "Good" << std::endl;
	} break;
	}
}

//Для того, чтобы анализировать полученные ошибки, а не просто обрушать программу, предусмотрена специальная конструкция try{}catch(){}
void try_catch_exception_stack_test() {
	std::cout
		<< "1) Normal stack work\n"
		<< "2) Stack overflow\n"
		<< "3) Pop from an empry stack\n"
		<< std::endl;

	int i;
	std::cin >> i;
	ExceptionStack est(5);

	try {
		switch (i) {
		case 2: {
			est.push(-1); est.push(-1);
		}
		case 3: {
			std::cout << est.pop() << std::endl;
		}
		case 1: {
			for (int cnt = 0; cnt != 5; ++cnt)
				est.push(cnt);
			for (int cnt = 0; cnt != 5; ++cnt)
				std::cout << est.pop() << ' ';
			std::cout << std::endl;
			std::cout << "Good" << std::endl;
		} break;
		}
	}
	catch (std::string str) {
		std::cout << "Error: " << str << std::endl;
	}
}

//Конструкция try{}catch(){} допускает не один, а несколько блоков catch(){} для различных типов исключений
//Представим себе функцию, которая может генерировать (выбрасывать) исключения различного типа: целый числа (int) и строки (string)
int different_exceptions(int x) {
	switch (x) {
	case 1:
		throw std::string("String Exception");
	case 2:
		throw -1;
	case 3:
		throw 3.14;
	}
	return x;
}

void different_exceptions_test() {
	std::cout
		<< "1) Throw string\n"
		<< "2) Throw integer\n"
		<< "3) Throw double\n"
		<< "Ohter - Normal workflow"
		<< std::endl;

	int i;
	std::cin >> i;
	try {
		std::cout << "Normal workflow: " << different_exceptions(i) << std::endl;
	}
	catch (int i) {
		std::cout << "Integer exception has been caught! " << i << std::endl;
	}
	catch (std::string str) {
		std::cout << "String exception has been caught!" << str << std::endl;
	}
}

//Как видно из теста, те исключения, которые были обозначены в блоках catch были пойманы, сработал код соответствующих блоков
//Те исключения, которые не обозначены в блоках catch, сломали программу

//Среди всех catch блоков есть один специальный, который ловит все возможные исключения
void any_exception_catcher() {
	std::cout
		<< "1) Throw string\n"
		<< "2) Throw integer\n"
		<< "3) Throw double\n"
		<< "Ohter - Normal workflow"
		<< std::endl;

	int i;
	std::cin >> i;
	try {
		std::cout << "Normal workflow: " << different_exceptions(i) << std::endl;
	}
	catch (...) {
		std::cout << "Some exception has been caught. I'dont know exact type of one." << std::endl;
	}
}

//если размещать несколько блоков catch, то может возникнуть вопрос: зависит ли выбор блока catch от порядка и как подбираются блоки, если типы похожи

void catch_order_testA() {
	std::cout
		<< "1) Throw string\n"
		<< "2) Throw integer\n"
		<< "3) Throw double\n"
		<< "Ohter - Normal workflow"
		<< std::endl;

	int i;
	std::cin >> i;
	try {
		std::cout << "Normal workflow: " << different_exceptions(i) << std::endl;
	}
	catch (double d) {
		std::cout << "A double has been caught: " << d << std::endl;
	}
	catch (int i) {
		std::cout << "An int has been cauth: " << i << std::endl;
	}
	catch (...) {
		std::cout << "Some exception has been caught." << std::endl;
	}
}

//Если универсальный блок catch(...) переставить с другими блоками, то возникнет ошибка компиляции
//Дело в том, что блоки catch проверяются СВЕРХУ ВНИЗ и первое попавшееся совпадение срабатывает, тогда, разместив универсальный блок сверху, мы сделали все остальные блоки заведомо недостижимыми

//при работе с системой подтипов можно попасть в неприятности
#include <stdexcept>
int different_exceptionsB(int x) {
	switch (x) {
	case 1:
		throw std::runtime_error("Runtime error exception");
	case 2:
		throw std::range_error("Range error exception"); //range_error наследует runtime_error
	}
	return x;
}

void different_exceptionsB_test() {
	std::cout
		<< "1) To throw runtime_error\n"
		<< "2) To throw range_error\n"
		<< "Other value - normal workflow\n"
		<< std::endl;

	int i;
	std::cin >> i;
	try {
		std::cout << "Normal workflow: " << different_exceptionsB(i) << std::endl;
	}
	catch (std::runtime_error &re) {
		std::cout << "Runtime error catch block: " << re.what() << std::endl;
	}
	catch (std::range_error &re) {
		std::cout << "Range error catch block: " << re.what() << std::endl;
	}
} //блок для родительского типа находится выше блока для дочернего типа, таким образом, блок для дочернего типа никогда не будет выполнен

int main() {
	if (false) exception_divv_test();
	if (false) exceptional_stack_test();
	if (false) try_catch_exception_stack_test();
	if (false) different_exceptions_test();
	if (false) any_exception_catcher();
	if (false) catch_order_testA();
	if (false) different_exceptionsB_test();

	return 0;
}