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
		std::cout << "Preliminary pop: " << est.pop() << std::endl;
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


int main() {
	if (false) exception_divv_test();
	if (false) exceptional_stack_test();

	return 0;
}