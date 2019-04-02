#include <iostream>

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

int main() {
	if (true) destructor_test1();

	return 0;
}