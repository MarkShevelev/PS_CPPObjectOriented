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

//�������, ��� ����� ���� �� �������� ������������ if �� ����� � �������
//������ �� ����, ��� ������ ������ ���� ��������� �������
//�� ������ ����� �� ���������� �����-�� ���
//� ������� ���� ������ ��� ������� �����������!

//�������� ������� �����
struct CommandProcess {
	virtual bool process() const { return true; } //����� ������� ���������� ��� proceed, ���� �����������
	//����� �����������, ������ ��� �� ���������� ���� ��� ������ ���������� � �������� �������
};

struct Exit : CommandProcess {
	bool process() const { return false; } //������� Exit �������� ����� ���, ��� �� ������ ���������� false, �.�. ��������� ������ ���������
};

struct Add : CommandProcess {
	bool process() const {
		int a, b;
		std::cin >> a >> b;
		std::cout << (a + b) << std::endl;
		return true;
	}
};

//������������ �������� �������
#include <map>
void arithmetic_polymorphic() {
	std::map <std::string, CommandProcess*> commands;
	Exit exit;
	Add add;
	commands["exit"] = &exit;
	commands["add"] = &add;

	bool proceed = true;
	while (proceed) {
		std::string command;
		std::cin >> command;

		auto process_it = commands.find(command); //���� ������ � �����, ������� ���������� ���������
		//���� �� �������, �� ��������� ��� ��� ��������� �������
		if (commands.end() == process_it) { std::cout << "Unknown command" << std::endl; continue; }

		//� ��������� ������� ���������� ������ ��������� �������
		proceed = process_it->second->process(); 
	}
}

int main() {
	if (false) arithmetic();
	if (false) arithmetic_polymorphic();

	return 0;
}