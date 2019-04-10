#include <iostream>
#include <algorithm>
#include <cstring>

//�������� ������ � ���������, ����������� ��������� �� ������������ ������
class StringA {
	char *data;
	size_t length;

public:
	StringA(char const *buff) {
		size_t length = strlen(buff);
		this->length = 0;
		if (nullptr != (data = new (std::nothrow) char[length + 1])) {
			std::copy(buff, buff + length + 1, data);
			this->length = length;
		}
	}

	StringA() : StringA("") {
	}

	void print() {
		if (nullptr == data)
			std::cout << "NULL" << std::endl;
		else
			std::cout << data << std::endl;
	}

	bool append(char const *buff) {
		size_t length = strlen(buff);
		if (!expand(this->length + length + 1)) return false;
		std::copy(buff, buff + length + 1, data + this->length);
		this->length += length;
		return true;
	}
	
	~StringA() {
		if (nullptr != data)
			delete[] data;
	}

private:
	bool expand(size_t new_length) {
		auto tmp = new (std::nothrow) char[new_length];
		if (nullptr == tmp) return false;
		std::copy(data, data + this->length + 1, tmp);
		delete[] data;
		data = tmp;
	}
};

void stringA_test() {
	StringA s1("Hello");
	s1.print();

	s1.append(" ");
	s1.print();

	s1.append("World");
	s1.append("!");

	s1.print();
}

//��� ������� ������� ����� ��������� �������
void stringA_fail() {
	StringA s1("Hello");
	StringA s2(s1);  //��� ����������� ���������� ������ �������� ���������� ������!

	s1.print();
	s2.print();

	//�� ���������� ����� ���� � �� �� ������ ����� ������� ������!
}

//����������� ����� ����������� � ��� �������� ��������� � �������
void print_stringA(StringA s) {
	s.print();
}

void stringA_fail2() {
	StringA s1("Hello");
	print_stringA(s1);
}

//���� ��� ������� �����������, �� �������� ������
void print_stringA_ref(StringA &s) {
	s.print();
}

void stringA_fail3() {
	StringA s1("Hello");
	print_stringA_ref(s1);
}

//��� ������� ����� �������� �� ������ �������������� ������������ �������� �������� �� ��� ������������
//� C++ � ����� ������� ���������� �������� ���� ����������� �����������
class StringB {
	char *data;
	size_t length;

public:
	StringB(char const *buff) {
		size_t length = strlen(buff);
		this->length = 0;
		if (nullptr != (data = new (std::nothrow) char[length + 1])) {
			std::copy(buff, buff + length + 1, data);
			this->length = length;
		}
	}

	StringB() : StringB("") {
	}

	//����������� �����������
	StringB(StringB const &src) : StringB(src.data) {//�� ���������� ������ ��� ������������� ������������
		std::cout << "Copying..." << std::endl;
	}

	void print() {
		if (nullptr == data)
			std::cout << "NULL" << std::endl;
		else
			std::cout << data << std::endl;
	}

	bool append(char const *buff) {
		size_t length = strlen(buff);
		if (!expand(this->length + length + 1)) return false;
		std::copy(buff, buff + length + 1, data + this->length);
		this->length += length;
		return true;
	}

	~StringB() {
		if (nullptr != data)
			delete[] data;
	}

private:
	bool expand(size_t new_length) {
		auto tmp = new (std::nothrow) char[new_length];
		if (nullptr == tmp) return false;
		std::copy(data, data + this->length + 1, tmp);
		delete[] data;
		data = tmp;
	}
};

void stringB_fail() {
	StringB s1("Hello");
	StringB s2(s1); //� ���� ������ ���������� ����������� �����������

	s1.print();
	s2.print();

	//�� ��������� �������, �.�. ������ ������ ������� ����, ���������� ������
}

void stringB_print(StringB b) {
	b.print();
}

void stringB_fail2() {
	StringB s1("Hello");
	stringB_print(s1);
}

//��� ���� ������ �������� ������ - ���� ������� ����������� �����������
//���������� ������ � ������� �������, ������� �������� ��������� �� ������ ����� ����� � �������� � �����������
class AutoArray {
	int *arr;
public:
	AutoArray(int *arr) {
		this->arr = arr;
	}

	AutoArray(AutoArray const &src) = delete; // = delete; - ��������, ��� ����� ���� �����, ����������� ����� �����������

	~AutoArray() {
		delete[] arr;
	}
};

void autoarray_test() {
	int *ptr = new (std::nothrow) int[10];
	AutoArray arr(ptr);
	//AutoArray arr2 = arr;//������ ����������!
}

int main() {
	//StringA
	if (false) stringA_test();
	if (false) stringA_fail();
	if (false) stringA_fail2();
	if (false) stringA_fail3();

	//StringB
	if (false) stringB_fail();
	if (false) stringB_fail2();

	return 0;
}