#include <iostream>

//� ��������� ��������� ��� ����� ������������� �������� ��������������
//�.�. �����-�� ������ ������ ������������� � ����������� ��� ����� C++, ��������, � int
//� ���� ������� ��������� �������������� ����

class Counter {
	int counter;
public:
	Counter(int begin) {
		counter = begin;
	}

	int next() {
		return counter++;
	}

	//��������� ���������� �������� �������������� ����
	operator int() {
		return counter;
	}
};

void print_int(int i) {
	std::cout << i << std::endl;
}

void print_int_test() {
	Counter c(10);
	print_int(c);
}

//��� ������������� ��������� �������������� �����, ��� � ������������, ����� ���� ��������� explicit
class IsPositive {
	int x;
public:
	IsPositive(int x) {
		IsPositive::x = x;
	}

	explicit operator bool() {
		return x > 0;
	}
};

void print_bool(bool b) {
	std::cout << std::boolalpha << b << std::endl;
}

void print_bool_test() {
	IsPositive neg(-1);
	//print_bool(neg); //�� ��������, �.�. �������������� ��������� explicit (�����)
	//������ ��-�������� ����� ��������� ����� ��������������
	//��� ����� ��������� ����� ���������
	print_bool((bool)neg); //C-style - ������ �� ����� ��
	print_bool(bool(neg)); //�++ - style - ������ ������ ������������
	print_bool(static_cast<bool>(neg)); //����� ����������� �������������� ����
}

//� ��������� ����� ������ ����� ������������ �� ������������ �������� �����/������
void std_cin_test() {
	int i;
	std::cin >> i;
	if (!std::cin) { //����� �� ���������� ��� ����, ��� std::cin ���������� � ���� bool: true - ����� � ���������� ���������, false - ������
		std::cout << "Not a number!" << std::endl;
	}
}

int main() {
	if (false) print_int_test();
	if (false) print_bool_test();
	if (false) std_cin_test();
}