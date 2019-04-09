#include <iostream>

//���������� �����, ������������ �������
class IntCounter {
	int i;
public:
	IntCounter(int i) { IntCounter::i = i; }
	IntCounter() : IntCounter(0) { }

	int next() { return i++; }
	void reset() { i = 0; }
};

//������ � ����������� � ���������� �������� � ������������ ������
void pointers_to_objects() {
	IntCounter c;           //�������� �������
	IntCounter &c_ref = c;  //������ �� ������
	IntCounter *c_ptr = &c; //��������� �� ������

	//��� ������ �� �������� ��� ������������ ������ � ���������
	for (int p = 0; p != 10; ++p)
		std::cout << c_ref.next() << " ";
	std::cout << std::endl;

	//��� ������ � ����������� ����� ������������ ������������� (*) � ->
	for (int p = 0; p != 10; ++p)
		std::cout << c_ptr->next() << " ";
	std::cout << std::endl;

	//�������� �������� � ������������ ������
	IntCounter *new_default = new (std::nothrow) IntCounter(); //��� ����������
	IntCounter *new_param = new (std::nothrow) IntCounter(-10); //� ����������
	IntCounter *new_array = new (std::nothrow) IntCounter[10];

	delete new_default;
	delete new_param;
	delete[] new_array;

}

//������� ����� ��� ������ �������� ��������� this
class ThisAware {
	int index;
public:
	ThisAware(int index) {
		ThisAware::index = index;
	}

	void print() {
		std::cout << index << ": " << this << std::endl;
	}
};

//this - ��� �������� �����, ������� ��������� �������� ����� �������, �� ������� ��� ������ �����
void this_test() {
	ThisAware a1(1), a2(2), a3(3);
	std::cout << &a1 << " ";
	a1.print();

	std::cout << &a2 << " ";
	a2.print();

	std::cout << &a3 << " ";
	a3.print();
} 

//������������� ��������� ����� this, ��� ���� ����� ��������� ���������� �����
class ThisAware2 {
	int index;
public:
	ThisAware2(int index) {
		//this - �����, � ���� ����� ��������� �������������
		this->index = index;
	}

	void print() {
		std::cout << this->index << ": " << this << std::endl;
	}
};

//������������� ��������� ����� this �� ����������� ���������� ��������
class ThisAware3 {
	int index;
public:
	ThisAware3(int index) {
		this->index = index;
	}

	bool check(ThisAware3 *address) {
		return this == address;
	}
};

void address_check_test() {
	ThisAware3 a(1);
	ThisAware3 b(2);
	ThisAware3 &a_ref = a;

	std::cout << std::boolalpha << a.check(&b) << " " << a.check(&a_ref) << std::endl;
}

int main() {
	if (false) pointers_to_objects();
	if (false) this_test();
	if (false) address_check_test();

	return 0;
}