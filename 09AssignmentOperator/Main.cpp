#include <iostream>
#include <cstring>

//����� �� ������� 08CopyConstructor
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

//������������� ������ StringB ����� ��������� � ������� ��� ������������� ������������
void assignment_stringB() {
	StringB s1("Hello");
	StringB s2("World");
	s1.print();
	s2.print();

	s2 = s1;
	s2.print();
} //���������� ������ ������ ��-�� �������� ��������

//����� ���������� �� ���� ��������, � ����� �++ ������� ����������� �������� ������������
class StringC {
	char *data;
	size_t length;

public:
	StringC(char const *buff) {
		size_t length = strlen(buff);
		this->length = 0;
		if (nullptr != (data = new (std::nothrow) char[length + 1])) {
			std::copy(buff, buff + length + 1, data);
			this->length = length;
		}
	}

	StringC() : StringC("") {
	}

	//����������� �����������
	StringC(StringC const &src) : StringC(src.data) {//�� ���������� ������ ��� ������������� ������������
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
	
	StringC& operator=(StringC const &src) {
		std::cout << "Assignment..." << std::endl;
		StringC tmp(src); //������ ����� ������ �� src, ��� ���� ����� �������� ����� ������
		if (nullptr == tmp.data) return *this;
		std::swap(this->data, tmp.data);  //���������� ������ ����� ����� �������� � ���������
		std::swap(this->length, tmp.length);
	} //�.�. ���� ������ ������ � ���������� �������, �� ��� ����� �� ������� ������������� �� ���������� ������

	~StringC() {
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

void assignment_string�() {
	StringC s1("Hello");
	StringC s2("World");
	s1.print();
	s2.print();

	s2 = s1;
	s2.print();
} //������������ �������!

int main() {
	if (false) assignment_stringB();
	if (false) assignment_string�();

	return 0;
}