#include <iostream>
#include <string>

//Стек - это безадресная структура данных, которая работает по принципу "последний вошёл, первый вышел" (LIFO - last in, first out)
//Стек является хранищем данных, в котором доступ можно получить только к одному определённому элементу
//какой именно это будет элемент определяется принципом LIFO
//По принципу LIFO при обращении к структуре из неё будет выбран тот элемент, который вошёл в неё последним
//Например, если мы складываем символы в стек 'a' -> 'b' -> 'c' -> 'b', то при попытке взять один элемент из стека мы получим 'd', т.к. 'd' вошёл последним.

//Стек очень лекго ораганизовать, используя vector
//мы будем хранить в стеке элементы любого типа, одного, но любого; это можно осуществить с использованием шаблона класса

#include <vector>
template <typename T>
class MyStack {
public: //основыне методы MyStack
	 //добавлением элемента в стек
	void push(T const &t) { elements.push_back(t); }

	//удаление последнего вошедшего элемента из стека
	//если стек пуст - поведение не определено!
	T pop() { auto t = std::move(elements.back()); elements.pop_back(); return t; }

	//пуст ли стек?
	bool empty() { return elements.empty(); }

	//сколько осталось элементов в стеке?
	size_t size() { return elements.size(); }

	//полная ёмкость стека
	size_t capacity() {return elements.capacity(); }

private:
	size_t top; //индекс вершины стека
	std::vector<T> elements; //vector хранит значения элементов стека
};

void my_stack_test() {
	MyStack<char> stack; //новый стек
	stack.push('a'); stack.push('b'); stack.push('c'); stack.push('d');
	while (!stack.empty())
		std::cout << stack.pop() << ' ';
	std::cout << std::endl;
}

//В STL существую специальная "обёртка", которая позволяет "превратить" vector в stack
#include <stack>
void stl_stack_test() {
	std::stack<int, std::vector<int>> stack; //шаблон имеет два параметра: тип хранимых данных и класс, который будет контейнером для хранения
	stack.push(3); stack.push(5); stack.push(-1); stack.push(7);
	while (!stack.empty()) {
		//stack.top() предоставляет ссылку на последний элемент стека, что позволяет обратиться к нему, не вынимая, это, в свою очередь, позволяет получить данные с вершины константного стека
		std::cout << stack.top() << ' ';
		stack.pop();
	}
}

//вторая важная безадресная структура данных - это очередь
//Очередь - это безадресная структура данных, которая работает по принципу "первый вошёл, первый вышел" (FIFO - first in, first out)
//Очередь является хранищем данных, в котором доступ можно получить только к одному определённому элементу
//какой именно это будет элемент определяется принципом FIFO
//По принципу FIFO при обращении к структуре из неё будет выбран тот элемент, который вошёл в неё первым
//Например, если мы складываем символы в очередь 'a' -> 'b' -> 'c' -> 'b', то при попытке взять один элемент из стека мы получим 'a', т.к. 'a' вошёл первым.

//организовать очередь с использованием стека сложно, т.к. при работе с очередью нам необходимо сдвигать начало очереди
//это можно сделать либо изменив индекс начала очереди, либо удалив первый элемент
//первое приведёт к большому расходу памяти, второе - сильному замедлению из-за копирования
//для решения этой проблемы в c++ есть специальный контейнер, очень похожий на vector
//deque - контейнер, который обеспечивает амортизированное константное время добавления как в конец, так и в начало
//в контейнере можно получить доступ к любому элементу через квадратные скобки по индексу
//элементы deque расположены не последовательно! Обход deque от начала до конца занимает больше времени, чем для vector

#include <deque>
//Реализуем очередь через deque
template <typename T>
class MyQueue {
public:
	void push(T const &t) { elements.push_back(t); }
	T& peek() { return elements.front(); }
	T const& peek() const { return elements.front(); }
	T poll() { auto t = std::move(elements.front());  elements.pop_front(); return t; }
	bool empty() const { return elements.empty(); }
	size_t size() const { return elements.size(); }

private:
	std::deque<T> elements;
};

void my_queue_test() {
	MyQueue<std::string> queue;
	queue.push("Hello"); queue.push(" "); queue.push("World"); queue.push("!");

	while (!queue.empty())
		std::cout << queue.poll() << '#';
	std::cout << std::endl;
}


int main() {
	if (false) my_stack_test();
	if (false) stl_stack_test();
	if (false) my_queue_test();
}