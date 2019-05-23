#include <iostream>

//Стек - это безадресная структура данных, которая работает по принципу "последний вошёл, первый вышел" (LIFO - last in, first out)
//Стек является хранищем данных, доступ можно получить только к одному элементу, но не к любому, а к определённому
//какой именно это будет элемент определяетс принципом LIFO
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

int main() {
	if (false) my_stack_test();
}