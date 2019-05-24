#include <iostream>
#include <string>

//vector � deque ���� ����������� ������� ������� � ����� � � ������, ������ ������� � �������� ��� ����� ����������� �������� � ����������� ������ � �����������
//���� ��� deque ����� ����������� �������� ������ �������
//��� �������� ������� � ������������ ����� vector ��� deque ����� �� ����������� ��������� � ������ ����� ��������� ������������
//� ���� ������� ����� ���������� �������� "������"

//������ - ��� ��������� ������ "����������������� �������", � ������� ���������� ����� ������ � ��������� ��������, ���� �������� �������
//������ �� ������� ����, ����� �������� ������ ������������� � ������, ������ ���������� ������ �������� ����� ���� �������� ����� ������, ������� ���������������� �������

//������ ���������� ������
template <typename T>
struct ListNode {
	T data;
	ListNode<T> *next = nullptr; //����� ���������� ��������
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

	//���� ������ ����, ��������� �� ����������
	ListNode<T>* Front() { return head; }
	ListNode<T> const* Front() const { return head; }

	bool empty() const { return nullptr == head; }

	//���� ��� ������� � �������� �� ��������� ����������� ����� ��������, ��� ����������� �� ���������� � ����������������� ��������� ������
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

//� ����������� ���������� ����� C++ ���� ���������� ��������� ������, ���������� ���� ���� - forward_list
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
