#include <iostream>
#include <string>

//���� - ��� ����������� ��������� ������, ������� �������� �� �������� "��������� �����, ������ �����" (LIFO - last in, first out)
//���� �������� �������� ������, � ������� ������ ����� �������� ������ � ������ ������������ ��������
//����� ������ ��� ����� ������� ������������ ��������� LIFO
//�� �������� LIFO ��� ��������� � ��������� �� �� ����� ������ ��� �������, ������� ����� � �� ���������
//��������, ���� �� ���������� ������� � ���� 'a' -> 'b' -> 'c' -> 'b', �� ��� ������� ����� ���� ������� �� ����� �� ������� 'd', �.�. 'd' ����� ���������.

//���� ����� ����� �������������, ��������� vector
//�� ����� ������� � ����� �������� ������ ����, ������, �� ������; ��� ����� ����������� � �������������� ������� ������

#include <vector>
template <typename T>
class MyStack {
public: //�������� ������ MyStack
	 //����������� �������� � ����
	void push(T const &t) { elements.push_back(t); }

	//�������� ���������� ��������� �������� �� �����
	//���� ���� ���� - ��������� �� ����������!
	T pop() { auto t = std::move(elements.back()); elements.pop_back(); return t; }

	//���� �� ����?
	bool empty() { return elements.empty(); }

	//������� �������� ��������� � �����?
	size_t size() { return elements.size(); }

	//������ ������� �����
	size_t capacity() {return elements.capacity(); }

private:
	size_t top; //������ ������� �����
	std::vector<T> elements; //vector ������ �������� ��������� �����
};

void my_stack_test() {
	MyStack<char> stack; //����� ����
	stack.push('a'); stack.push('b'); stack.push('c'); stack.push('d');
	while (!stack.empty())
		std::cout << stack.pop() << ' ';
	std::cout << std::endl;
}

//� STL ��������� ����������� "������", ������� ��������� "����������" vector � stack
#include <stack>
void stl_stack_test() {
	std::stack<int, std::vector<int>> stack; //������ ����� ��� ���������: ��� �������� ������ � �����, ������� ����� ����������� ��� ��������
	stack.push(3); stack.push(5); stack.push(-1); stack.push(7);
	while (!stack.empty()) {
		//stack.top() ������������� ������ �� ��������� ������� �����, ��� ��������� ���������� � ����, �� �������, ���, � ���� �������, ��������� �������� ������ � ������� ������������ �����
		std::cout << stack.top() << ' ';
		stack.pop();
	}
}

//������ ������ ����������� ��������� ������ - ��� �������
//������� - ��� ����������� ��������� ������, ������� �������� �� �������� "������ �����, ������ �����" (FIFO - first in, first out)
//������� �������� �������� ������, � ������� ������ ����� �������� ������ � ������ ������������ ��������
//����� ������ ��� ����� ������� ������������ ��������� FIFO
//�� �������� FIFO ��� ��������� � ��������� �� �� ����� ������ ��� �������, ������� ����� � �� ������
//��������, ���� �� ���������� ������� � ������� 'a' -> 'b' -> 'c' -> 'b', �� ��� ������� ����� ���� ������� �� ����� �� ������� 'a', �.�. 'a' ����� ������.

//������������ ������� � �������������� ����� ������, �.�. ��� ������ � �������� ��� ���������� �������� ������ �������
//��� ����� ������� ���� ������� ������ ������ �������, ���� ������ ������ �������
//������ ������� � �������� ������� ������, ������ - �������� ���������� ��-�� �����������
//��� ������� ���� �������� � c++ ���� ����������� ���������, ����� ������� �� vector
//deque - ���������, ������� ������������ ���������������� ����������� ����� ���������� ��� � �����, ��� � � ������
//� ���������� ����� �������� ������ � ������ �������� ����� ���������� ������ �� �������
//�������� deque ����������� �� ���������������! ����� deque �� ������ �� ����� �������� ������ �������, ��� ��� vector

#include <deque>
//��������� ������� ����� deque
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

//��� ������ � �������� � STL ���������� ������ ��� ����������� deque - queue
#include <queue>
void stl_queue_test() {
	std::queue<std::string, std::deque<std::string>> hello_queue;
	hello_queue.push("Hello"); hello_queue.push(" "); hello_queue.push("Queue"); hello_queue.push("!");
	while (!hello_queue.empty()) {
		std::cout << hello_queue.front();
		hello_queue.pop();
	}
	std::cout << std::endl;
}

//������ ������ ����������� ��������� - ��� ������� � �����������
//�������� ������� ������� � �����������, �� ������� ������� � ���, ��� �������� ��� ������ �� ������� ������� �� ������ �������� FIFO, �� ������� ����������
//���������� ������: ���� ���� � �� ����� ��������� �� �� �������� ���, ��� ����� ������� �������� �������
//��� �������� � ������� � ������������ ������� {Anna,27}, {Bert,34}, {Uncle Bob, 57}, {Duke,40}, {Cory,27}
//�������� ����� ����� �� ������� � ��������� �������: {Uncle Bob, 57} -> {Duke,40} -> {Bert,34} -> {Anna,27} -> {Cory,27}
//������� ��������� ������������ ���������, ���� ������� ��������, �� ��������� ������� FIFO

//������� ���������� ����� �������, ����� �� ������ ���� ���������� �������� �������, ����������������� ��� ������������ �� ���������� ����������, ����������� ������ - ������������� �������� ����
//� �� ����� ������������� ������, � STL ���� ������, ������� ���� ��������� ��� ����������� ��������: priority_queue
#include <queue>

struct User {
	std::string name;
	int age;
};
std::ostream& operator<<(std::ostream &os, User const &u) {
	return os << "{ \"" << u.name << "\" , " << u.age << " }";
}

//priority_queue ���������� �� ��������� ���������� <
bool operator<(User const &lha, User const &rha) {
	return lha.age < rha.age;
}

void stl_priority_queue_test() {
	std::priority_queue<User> users;
	users.push({ "Anna",27});
	users.push({ "Bert",34 });
	users.push({ "Uncle Bob", 57 });
	users.push({ "Duke" ,40 });
	users.push({ "Cory",27 });

	while (!users.empty()) {
		std::cout << users.top() << std::endl;
		users.pop();
	}
}

int main() {
	if (false) my_stack_test();
	if (false) stl_stack_test();
	if (false) my_queue_test();
	if (false) stl_queue_test();
	if (false) stl_priority_queue_test();
}