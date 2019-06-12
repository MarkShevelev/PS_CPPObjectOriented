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

//��������� ���������� �������

//���� ���������� �� ������������ ���, �� ���������� ����, ��� � ������� ������ ��� ��� ������������� ��������� ������� ����������, �.�. ��� ������� �� ����� ������������
//��� �� �����, �� ������� ���� ���������� ��������� ���
//��� ����� �������� � C++ ������������ ����������� ���������� - ����� ����������� ������ (pure virtual)
//�� �����, ��� ����������� ����� - ��� ��������� �� �����-�� ���, �������� ���� ��������� ����� ���� � ���������� ������
//������������ �� ����� �� ������ ������� ����� ��������� � �������� � ���� nullptr
//������ ����� �������� � ���������� ����� ����������� 

struct Figure { //������� ������ �� ����� �������� ����������� ��������� ��� �������
	virtual double periphery() const = 0; //����� ����������� �������
	virtual double area() const = 0; //����� ����������� �������
};

class Circle : public Figure {
public:
	Circle(double r) :r(r) { }

	double periphery() const override { return 3.14*r*2.; } //��� ������ ����� ������� ����� ���������
	double area() const override { return 3.14*r*r; }

private:
	double r;
};

class Rectangle : public Figure {
public:
	Rectangle(double w, double h): w(w), h(h) { }

	double periphery() const { return 2 * (w + h); } //��� ������ ����� ������� ����� ���������
	double area() const { return w * h; }

private:
	double w, h;
};

void print_figure(Figure const &fig) {
	std::cout << "periphery = " << fig.periphery() << " and area = " << fig.area() << std::endl;
}

void figure_test() {
	//Figure fig; //������ ����������
	//���������� ������� ��������� ������ � ����� ������������ ���������, ��� ��� ����� �� ������ ����� ��������
	
	//�� ����� ������� ������ ���� Figure �� ������������ �������
	Circle cir(1);
	print_figure(cir);

	Rectangle rect(2, 3);
	print_figure(rect);
}

//������, ��� ������ ������� ����� ����������� (pure virtual) � �������� (public), � ���������� ������ ����������� (�� �����������, ��������, ����������� ��������), ���������� "����������".

//������ � ������������ ������ ������� ������� ������� ����� ��� �����������
//i) ���������� �� ����� �������������� � �������� �������, �.�. ��� ���������� ������
//ii) ���������� ������ ���������� ������ ������������, ������ ������ ������ ��� �������
//iii) ���������� ����������, ��� ����� ������ � ����������� ����� ������, ����������, �� �� ������������ � ���, ��� ��� ������ � ��������, ��� ������ ������� ����������� ����


//������ ��� �������� �������� ������ ����� ������� �� ����� ������� ����� ������������
//���� � ������ ������������ � ����� ������������ �������� ���� ������ ��� ������� ������, ��� ����������� ������ � �����������, �� ����� ������ �� �������� "������������"

struct HtmlResponce { //��� ���������
	virtual std::string header() const = 0; //� ������� ������ ���� ���������
	virtual std::string body() const = 0; //� ������� ����� ���� ����
};

struct GoodPage : HtmlResponce { //����������� �����
	std::string header() const override final { return "HTTP/1.1 200 OK"; } //� ���� �������, ������� ������� �������� ����� ���������, ��� ����� ������� � ������� ����� ��� ���� ������� �������
	//� ��� ���� ������ ����� ���� ������
};

struct MainPage : GoodPage {
	std::string body() const override { return "Main page"; } //��� ���������� ����� ������������ ������
};

//����������� ����� ����������� ������ ����� �� ������� ���� ���� ����� ����������� �����, ����� ��� ��� �� �����������, � ����� ������� �����
//��� ��� � ����������� ������ ���� ����� ����������� �����, �� ������� ������������ ������ ������ �������

int main() {
	if (false) arithmetic();
	if (false) arithmetic_polymorphic();
	if (false) figure_test();

	return 0;
}