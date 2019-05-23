#include <iostream>

//���� - ��� ����������� ��������� ������, ������� �������� �� �������� "��������� �����, ������ �����" (LIFO - last in, first out)
//���� �������� �������� ������, ������ ����� �������� ������ � ������ ��������, �� �� � ������, � � ������������
//����� ������ ��� ����� ������� ����������� ��������� LIFO
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

int main() {
	if (false) my_stack_test();
}