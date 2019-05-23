#include <iostream>

//—тек - это безадресна€ структура данных, котора€ работает по принципу "последний вошЄл, первый вышел" (LIFO - last in, first out)
//—тек €вл€етс€ хранищем данных, доступ можно получить только к одному элементу, но не к любому, а к определЄнному
//какой именно это будет элемент определ€етс принципом LIFO
//ѕо принципу LIFO при обращении к структуре из неЄ будет выбран тот элемент, который вошЄл в неЄ последним
//Ќапример, если мы складываем символы в стек 'a' -> 'b' -> 'c' -> 'b', то при попытке вз€ть один элемент из стека мы получим 'd', т.к. 'd' вошЄл последним.

//—тек очень лекго ораганизовать, использу€ vector
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

	//полна€ Ємкость стека
	size_t capacity() {return elements.capacity(); }

private:
	size_t top; //индекс вершины стека
	std::vector<T> elements; //vector хранит значени€ элементов стека
};

void my_stack_test() {
	MyStack<char> stack; //новый стек
	stack.push('a'); stack.push('b'); stack.push('c'); stack.push('d');
	while (!stack.empty())
		std::cout << stack.pop() << ' ';
	std::cout << std::endl;
}

//¬ STL существую специальна€ "обЄртка", котора€ позвол€ет "превратить" vector в stack
#include <stack>
void stl_stack_test() {
	std::stack<int, std::vector<int>> stack; //шаблон имеет два параметра: тип хранимых данных и класс, который будет контейнером дл€ хранени€
	stack.push(3); stack.push(5); stack.push(-1); stack.push(7);
	while (!stack.empty()) {
		//stack.top() предоставл€ет ссылку на последний элемент стека, что позвол€ет обратитьс€ к нему, не вынима€, это, в свою очередь, позвол€ет получить данные с вершины константного стека
		std::cout << stack.top() << ' ';
		stack.pop();
	}
}

int main() {
	if (false) my_stack_test();
	if (false) stl_stack_test();
}