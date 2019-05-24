#include <iostream>
#include <string>
#include <random>

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
	MyList() { }

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
	//явно удаляем опасные операции
	MyList<T>& operator=(MyList<T> const &oth) = delete;
	MyList(MyList<T> const &src) = delete;

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
#include <iterator> //std::next
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

//forward_list обладает серьёзными ограничениями, например, мы не можем вставить элемент "перед" заданным, т.к. предыдущий элемент неизвестен
//движение итератора возможно только вперёд ++it, потому нельзя быстро обратиться к последнему элементу

//эту проблему можно решить, пожертвовав немного памятью, чтобы у каждого элемента была ссылка как на последующий, так и на предыдущий
//такой список называется двунаправленным или двусвязным (doubly linked list)
//в STL двусвязный список реализован контейнером list

#include <list>
// Вспомогательная функция, позволяющая "зациклить" список
template <typename Container, typename ForwardIt>
ForwardIt LoopIterator(Container& container, ForwardIt pos) {
	return pos == container.end() ? container.begin() : pos;
}

template <typename T>
void josephus_permutation(std::vector<T> &elements, unsigned step_size) {
	std::list<T> pool;
	for (auto it = elements.begin(), end = elements.end(); it != end; ++it) {
		pool.push_back(std::move(*it));
	}
	auto first = elements.begin();
	auto cur_pos = pool.begin();
	while (!pool.empty()) {
		*(first++) = std::move(*cur_pos);
		if (pool.size() == 1) {
			break;
		}
		const auto next_pos = LoopIterator(pool, std::next(cur_pos));
		pool.erase(cur_pos); //если бы это был vector, то эта операция была бы о-о-очень долгой
		cur_pos = next_pos;
		for (unsigned step_index = 1; step_index < step_size; ++step_index) {
			cur_pos = LoopIterator(pool, std::next(cur_pos));
		}
	}
}

void josephus_permutation_test() {
	std::vector<std::string> players = { "Anna","Bert","Corey","Uncle Bob","Duke" };
	int step;
	std::cin >> step;
	josephus_permutation(players, step);

	for (auto &player : players)
		std::cout << player << ' ';
	std::cout << std::endl;
}


int main() {
	if (false) my_list_test();
	if (false) stl_forward_list_test();
	if (false) josephus_permutation_test();
}
