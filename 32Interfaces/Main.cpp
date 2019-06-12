#include <iostream>
#include <string>

//���������� ��������� ������: �������� ��������� � ���������� �����������
//�������� exit - ����� �� ���������
//�������� add mul � sub - ����������� ���� ����� � ������� �����, ������������ ��� ��������, ��������������
//�������� div ���������� ��� ����� � ���� �������� ����� ����� �� �������, ���� ��������, ��� ������������ ������� �� ����

//����� �� �� ������ ��� ������ ���:

void arithmetic() {
	bool proceed = true;
	while (proceed) {
		std::string command;
		std::cin >> command;

		if ("exit" == command) { proceed = false; continue; }
		if ("add" == command) {
			int a, b;
			std::cin >> a >> b;
			std::cout << (a + b) << std::endl;
			continue;
		}

		if ("mul" == command) {
			int a, b;
			std::cin >> a >> b;
			std::cout << (a * b) << std::endl;
			continue;
		}

		if ("sub" == command) {
			int a, b;
			std::cin >> a >> b;
			std::cout << (a - b) << std::endl;
			continue;
		}

		if ("div" == command) {
			int a, b;
			std::cin >> a >> b;
			if (0 == b) { std::cout << "Division by zero!" << std::endl; }
			else { std::cout << (a / b) << std::endl; }
			continue;
		}

		std::cout << "Unknown command" << std::endl;
	};
}

int main() {
	if (false) arithmetic();

	return 0;
}