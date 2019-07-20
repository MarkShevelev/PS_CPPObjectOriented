#include <iostream>
#include <string>
#include <unordered_map>

//��������� �������, ������� ��������� ������� ������������� �������� ������ ������
struct Command {
	virtual bool process() const = 0;
	virtual ~Command() { }
};

//����� CommandLineProcess ��������� ������������� �������� ������ ������
class CommandLineProcess final {
public:
	void run() const { //�������� �����, ������� ���������� map ����� � ������ ��� ������
		bool proceed = true;
		while (proceed) {
			std::string user_command;
			std::cin >> user_command;
			auto command_it = command_processes.find(user_command); //���������� ����� � map command �� ����� - �������� ������
			if (command_it != command_processes.end()) {
				proceed = command_it->second->process(); //���� ����� �������, �� ��������� � �������� ����� - ����� �� ����������
				//���� ������� ����� false, �� �� ��������� ����
			}
			else {//����� �� ������, ���� ������� �� ���� �������
				std::cout << "Unknown command!" << std::endl;
			}
		}
	}

private:
	//���������� ������ - ��� map, ������� ������ ������������ ������ �������� ������ �����-�� �������, �� ����������� ��������� � �� ����������� ����������� ������ ����� ������� CommandLineProcess
	//��������� ����� CommandLineProcess � Command - ���������
	//��� ��������� �� �������� shared_ptr
	std::unordered_map<std::string, std::shared_ptr<Command>> command_processes;

public:
	//����������� ��� ������������� command_processes
	CommandLineProcess(std::unordered_map<std::string, std::shared_ptr<Command>> command_processes): command_processes(command_processes) { }
};

//��������� ���������� ������� Exit
//������ ���� ������� - ���������� ������, �.�. ����� process ������ ���������� false
struct Exit final : Command {
	virtual bool process() const override { return false; } //��, ��� ������ ��� �������, ���������� ���� ��� ���������� ����� � ������ run � ������ CommandLineProcess
};

//����� SimpleApp ���������� ���������� ���������� � �������� ������
//����� ���������� ������������ ������ ���� ������� - exit
//�� ���� ��������� ������� ��������� Unknown command
class SimpleApp final {
	//����������� ����� ��������� ��� ��� ������������� map ��� CommandLineProcess � ������������ SimpleApp
	static auto map_init() {
		//������ � ��������� map �������������� ������-�������
		std::unordered_map<std::string, std::shared_ptr<Command>> key_command;
		key_command["exit"] = std::make_shared<Exit>(); //�������� �������� shared_ptr ����������� ������� make_shared, ����� ������� ������ ���� �������������� ��������, � �� �����������, �����; ����� �� ���� �������������� ��������� �������������� � shared_ptr<Command>

		return key_command;
	}

public:
	SimpleApp(): clp(SimpleApp::map_init()) { }
	void run() const { clp.run(); }

private:
	CommandLineProcess const clp; //����������!
};

//���������� ��������� � �������������� ������� ������� ������
//��� ����� exit �����������, ��� ����� ����� ������ ������� ������� Unknown command
void simple_app_test() {
	SimpleApp().run();
}

//������ ������ �� ������������ ����������� ������
//����� ��������� �������, ������� ���� ���������� ������ � ���� ����� ���� �����������
class CountingCommand final: public Command {
public:
	virtual bool process() const override {
		std::cout << "The command called " << ++counter << " times" << std::endl;
		return true;
	}

private:
	mutable int counter = 0;
};

void app_with_counting_command() {
	using namespace std;
	unordered_map<string, shared_ptr<Command>> command_processes;
	command_processes["exit"] = make_shared<Exit>();
	command_processes["next"] = make_shared<CountingCommand>();

	CommandLineProcess(command_processes).run();
}

int main() {
	if (false) simple_app_test();
	if (false) app_with_counting_command();
}