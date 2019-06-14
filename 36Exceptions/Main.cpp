#include <iostream>
#include <string>

//� ��������� ������� ��� ���������� ������������ � ��������� ����������� ������������� ��������
//���������� ����� Stack

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

//�������� ������������� ������ Stack ������� � ���, ��� ��������� ������� ����� ��������� � �������� ������������� ��������� ���������
//�������� ����� push ����� ����������� � ������������� ������
//�� ����� �� ������� ��������, �� ��� �������� ������������ �� ������?
//�������� ������� �������� ���� bool, ������� ��������� ������ ����������
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

	bool pop(int &x) { //����� ������ �������� ����������� �� ������ pop :(
		if (0 == top) return false;
		x = data_ptr[--top];
		return true;
	}

	bool empty() const { return 0 == top; }

private:
	size_t max_size, top;
	int *data_ptr;
};
//������������� ����� � ������������ �������� �������� ��� ������ pop, �.�. �� �� ����� ������� �������� ��������� �� �������, � ��������� ��� ���������� �� ������
//�� ������ ��� � ���, ��� �� ����� ��������� ������ ����� ������ ����� �������� ��� ������ �������� ������������

bool add_numbers_to_stack(int *range_begin, int *range_end, CheckStack &st) {
	for (int *it = range_begin; it != range_end; ++it)
		if (st.push(*it)) return false; //���������� ����������� ��������
	return true; //� ���������� ������� �������� ��� ������ ������������� �����
}

//������ ��������� ���� �������� ������������
//���� � ������������ �� ������� �������� ������, �� ��� �� ����� �������� � �������?

//��� �� ���������� � ��������� ������ ������ ��� ����� ���������������� ���������� �������� "����������"



int main() {
	return 0;
}