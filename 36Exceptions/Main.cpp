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
//���������� - ��� �������� ���������� ���������� ������ ������� ��� ������ � ��������, ����� ��� �� ����� ������������� ���������, ��������, ������� ��������

//���������� ������� �������
int divv(int x, int y) {
	return x / y;
}

//����� ������� �������� �����������: ��� �� ����� ������� ������� ��������, ���� y == 0
//���� �� ���������� ����� ��������, �� ������ ����� �������� ������ �������, �� ��� ����������� ����� �� �������� ������� ����
int return_divv(int x, int y) {
	if (0 == y) return 0; //�� ��� �� ������ �������? ��� ������������ ������, ��� ��������� ������?
	return x / y;
}
//������ � return �� ���� ���������, �.�. �����������, ������� ���������� ���� �������, �� ������ �������� ���������� ������� ��������� �� ������ ������� �� ����
//����� ��� � ������� ����������!

int exception_divv(int x, int y) {
	if (0 == y) throw 0; //�������� ����� throw �������� � ���������� ������ �������
	return x / y;
}

void exception_divv_test() {
	int x, y;
	std::cin >> x >> y;
	std::cout << exception_divv(x, y) << std::endl;
}

//��� ������������� throw �������, ��� ���� ��������� ����������
//� ����� C++ ���������� - ��� ����� ��������, ������������ ���� ��� ������ ������ ������
//�������� ����� ��������� ������
//��������� Stack ����� ������������ ��������� ����������

class ExceptionStack {
public:
	ExceptionStack(size_t max_size) : max_size(max_size), top(0) {
		data_ptr = new (std::nothrow) int[max_size];
		if (nullptr == data_ptr) throw std::string("Not enough memory!");
	}

	void push(int x) {
		if (top == max_size) throw std::string("Stack overflow!");
		data_ptr[top++] = x;
	}

	int pop() {
		if (0 == top) throw std::string("Pop from an empty stack!");
		return data_ptr[--top];
	}

	bool empty() const { return 0 == top; }

private:
	size_t max_size, top;
	int *data_ptr;
};

void exceptional_stack_test() {
	std::cout
		<< "1) Normal stack work\n"
		<< "2) Stack overflow\n"
		<< "3) Pop from an empry stack\n"
		<< std::endl;

	int i;
	std::cin >> i;
	ExceptionStack est(5);
	switch (i) {
	case 2: {
		est.push(-1); est.push(-1);
	}
	case 3: {
		std::cout << est.pop() << std::endl;
	}
	case 1: {
		for (int cnt = 0; cnt != 5; ++cnt)
			est.push(cnt);
		for (int cnt = 0; cnt != 5; ++cnt)
			std::cout << est.pop() << ' ';
		std::cout << std::endl;
		std::cout << "Good" << std::endl;
	} break;
	}
}

//��� ����, ����� ������������� ���������� ������, � �� ������ �������� ���������, ������������� ����������� ����������� try{}catch(){}
void try_catch_exception_stack_test() {
	std::cout
		<< "1) Normal stack work\n"
		<< "2) Stack overflow\n"
		<< "3) Pop from an empry stack\n"
		<< std::endl;

	int i;
	std::cin >> i;
	ExceptionStack est(5);

	try {
		switch (i) {
		case 2: {
			est.push(-1); est.push(-1);
		}
		case 3: {
			std::cout << est.pop() << std::endl;
		}
		case 1: {
			for (int cnt = 0; cnt != 5; ++cnt)
				est.push(cnt);
			for (int cnt = 0; cnt != 5; ++cnt)
				std::cout << est.pop() << ' ';
			std::cout << std::endl;
			std::cout << "Good" << std::endl;
		} break;
		}
	}
	catch (std::string str) {
		std::cout << "Error: " << str << std::endl;
	}
}

//����������� try{}catch(){} ��������� �� ����, � ��������� ������ catch(){} ��� ��������� ����� ����������
//���������� ���� �������, ������� ����� ������������ (�����������) ���������� ���������� ����: ����� ����� (int) � ������ (string)
int different_exceptions(int x) {
	switch (x) {
	case 1:
		throw std::string("String Exception");
	case 2:
		throw 1;
	case 3:
		throw 3.14;
	}
	return x;
}

void different_exceptions_test() {
	std::cout
		<< "1) Throw string\n"
		<< "2) Throw integer\n"
		<< "3) Throw double\n"
		<< "Ohter - Normal workflow"
		<< std::endl;

	int i;
	std::cin >> i;
	try {
		std::cout << "Normal workflow: " << different_exceptions(i) << std::endl;
	}
	catch (int i) {
		std::cout << "Integer exception has been caught!" << std::endl;
	}
	catch (std::string str) {
		std::cout << "String exception has been caught!" << std::endl;
	}
}

//��� ����� �� �����, �� ����������, ������� ���� ���������� � ������ catch ���� �������, �������� ��� ��������������� ������
//�� ����������, ������� �� ���������� � ������ catch, ������� ���������

int main() {
	if (false) exception_divv_test();
	if (false) exceptional_stack_test();
	if (false) try_catch_exception_stack_test();
	if (false) different_exceptions_test();

	return 0;
}