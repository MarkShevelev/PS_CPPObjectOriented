#include <iostream>
#include <string>

//vector и deque дают возможность быстрой вставки в конце и в начало, однако вставка в середину для обоих контейнеров приводит к перемещению памяти и копированию
//хотя для deque такое перемещение занимает меньше времени
//при активной вставке в произвольное место vector или deque время на перемещение элементов в памяти может оказаться значительным
//в этих случаях более подходящим является "список"

//Список - это структура данных "последовательного доступа", в которой обратиться можно только к соседнему элементу, если известен текущий
//Список не требует того, чтобы элементы подряд располагались в памяти, потому добавление нового элемента может быть седелано очень быстро, простым перезаписыванием адресов

//пример реализации списка
template <typename T>
struct ListNode {
	T data;
	ListNode<T> *next = nullptr; //адрес следующего элемента
};

template <typename T>
class MyList {
public:
	void PushFront(T const &t) {
		ListNode<T> *new_node = new (std::nothrow) ListNode<T>{ t,head };
		head = new_node;
	}

	void PopFront() { 
		if (nullptr == head) return; 
		ListNode<T> *to_delete = head;
		head = head->next;
		delete to_delete;
	}

	//если список пуст, поведение не определено
	ListNode<T>* Front() { return head; }
	ListNode<T> const* Front() const { return head; }

	bool empty() const { return nullptr == head; }

	//даже при вставке и удалении мы совершаем константное число действий, вне зависимости от количества и месторасположения элементов списка
	void InsertAfter(ListNode<T> *node, T const &t) {
		if (nullptr == node) PushFront(t);
		ListNode<T> *new_node = new (std::nothrow) ListNode<T>{ t,node->next };
		node->next = new_node;
	}

	void RemoveAfter(ListNode<T> *node) {
		if (nullptr == node || nullptr == node->next) return;
		ListNode<T> *to_remove = node->next;
		node->next = to_remove;
		delete to_remove;
	}

	~MyList() {
		while (!empty()) PopFront();
	}

private:
	ListNode<T> *head = nullptr;
};

void my_list_test() {
	MyList<std::string> list;

	list.PushFront(" ");
	list.InsertAfter(list.Front(), "World");
	list.InsertAfter(list.Front()->next, "!");
	list.PushFront("Hello");

	ListNode<std::string> *element = list.Front();
	while (nullptr != element) {
		std::cout << element->data;
		element = element->next;
	}
	std::cout << std::endl;
}

//в стандартной библиотеке языка C++ есть реализация структуры данных, написанной нами выше - forward_list
#include <forward_list>
void stl_forward_list_test() {
	std::forward_list<std::string> words;
	words.push_front(" ");
	words.insert_after(words.begin(), "World");
	words.insert_after(next(words.begin()), "!");
	words.push_front("Hello");

	for (auto &element : words)
		std::cout << element;
	std::cout << std::endl;
}

int main() {
	if (false) my_list_test();
	if (false) stl_forward_list_test();
}
