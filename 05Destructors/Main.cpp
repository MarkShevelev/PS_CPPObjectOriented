#include <iostream>
#include <algorithm>

//������ ������������� � C++ ���� ����������� �������� ��� "���������������" (�����������) ��������,
//���� �������� ���������� �������� � ������� ������� ������������ ������ - �����������
//���� ����������� ���������� ���� ��� �� ����, ��� �� �������� ������������ ������, �������� ������,
//�� ���������� - ��� ��� �����������������
//���������� ��������� ���� ��� ����� ���, ��� ������ ������ ����������, ����

class WithDestructor {
private:
	int index;

public:
	WithDestructor(int in_index) { index = in_index;  std::cout << "Construct: " << index << std::endl; }

	//���������� ����������� ��� ������������� ����, ��� �����������, � �������� ��� ��������� � ��������� ������, �� �������������� �������� ���� ~
	~WithDestructor() { std::cout << "Destructor: " << index << std::endl; }
};

void destructor_test1() {
	WithDestructor object1(1);

	{
		WithDestructor object2(2);
	}

	WithDestructor object3(3);
}

//� ������� �� ������������ � ������ ����� ���� ������ ������ ���� ���������� � �� ����������� ���������� ��� ����������

//���������� ������������ ������� � �++ ���������� � ���������� ���������� ���������, ��������, ������������ �������
class IntArray {
	int *data;
	size_t size;

public:
	IntArray(size_t in_size) { 
		size = 0; 
		//����������� �������� ����������� ������
		if (nullptr != (data = new (std::nothrow) int[in_size]))
			size = in_size;
	}

	size_t getSize() { return size; }

	int get(size_t idx) {
		return data[idx];
	}

	void set(size_t idx, int x) {
		data[idx] = x;
	}

	//����� ��� ��������� �������������� ������������ ������
	bool resize(size_t new_size) {
		int *tmp = new (std::nothrow) int[new_size];
		if (nullptr == tmp) return false;
		std::copy(data, data + size, tmp);
		delete[] data;
		data = tmp;
		size = new_size;
		return true;
	}

	~IntArray() {
		//���������� ���������� ������ �������
		delete[] data;
	}
};

void destructor_test2() {
	IntArray arr(1);
	if (0 == arr.getSize()) {
		std::cout << "Can't initialize array" << std::endl;
		return;
	}

	int user_input; size_t pos = 0;
	do {
		std::cin >> user_input;
		if (0 == user_input) break;
		if (pos == arr.getSize() && !arr.resize(arr.getSize()*2)) {
			std::cout << "Not enought memory!" << std::endl;
			break;
		}

		arr.set(pos++, user_input);
		std::cout << arr.getSize() << std::endl;
	} while (true);
}

int main() {
	if (false) destructor_test1();
	if (false) destructor_test2();

	return 0;
}