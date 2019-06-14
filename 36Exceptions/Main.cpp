#include <iostream>
#include <string>

//¬ некоторых случа€х нам приходитс€ сталкиватьс€ с проблемой корректного возвращаемого значени€
//–ассмотрим класс Stack

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

//ѕроблема использовани€ класса Stack состоит в том, что несколько методов могут оказатьс€ в ситуации невозможности выполнить требуемое
//например метод push может столкнутьс€ с переполненным стеком
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

	bool pop(int &x) { //такой подход неудачно сказываетс€ на методе pop :(
		if (0 == top) return false;
		x = data_ptr[--top];
		return true;
	}

	bool empty() const { return 0 == top; }

private:
	size_t max_size, top;
	int *data_ptr;
};
//»спользование флага в возвращаемом значении неудобно дл€ метода pop, т.к. мы не можем вернуть значение нормально из функции, а вынуждены его записывать по ссылке
//не говор€ уже о том, что мы будем вынуждены тащить через каждый вызов операций над стеком проверки корректности

bool add_numbers_to_stack(int *range_begin, int *range_end, CheckStack &st) {
	for (int *it = range_begin; it != range_end; ++it)
		if (st.push(*it)) return false; //приходитс€ производить проверки
	return true; //и возвращать булевое значение при каждом использовании стека
}

//помимо неудобств есть проблема конструктора
//если в конструкторе не удастс€ выделить пам€ть, то как мы можем сообщить о поломке?

//ƒл€ со сложностью в обработке ошибок многие ќќѕ €зыки программировани€ используют механизм "»сключений"



int main() {
	return 0;
}