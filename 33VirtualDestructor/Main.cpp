#include <iostream>
#include <string>
#include <vector>

//������ �� ����� ��������� � ������������ ������ ������� ��������� ����, � ��������� ������ ����������
//���������� ������ � ��������
//������� � ������� ������ ������������� ���������� ��� �����������

struct Figure {
	virtual double periphery() const = 0; 
	virtual double area() const = 0;

	~Figure() { std::cout << "Figure destructor" << std::endl; }
};

class Circle : public Figure {
public:
	Circle(double r) :r(r) { }

	double periphery() const override { return 3.14*r*2.; }
	double area() const override { return 3.14*r*r; }

	~Circle() { std::cout << "Circle destructor" << std::endl; }

private:
	double r;
};

class Rectangle : public Figure {
public:
	Rectangle(double w, double h) : w(w), h(h) { }

	double periphery() const { return 2 * (w + h); }
	double area() const { return w * h; }

	~Rectangle() { std::cout << "Rectangle destructor" << std::endl; }

private:
	double w, h;
};

//��������� ������� ������������ ������ ������� �����
double full_area(std::vector<Figure*> const &figures) {
	double area = 0.;
	for (auto fig : figures)
		area += fig->area();
	return area;
}

//������: ������������ ����� ��������� ��������� ������ �������� ������ � ������ ��� ��, ��� ����������� � ������ �����
//���� ��� �������������� �������: exit � area
//exit - ����� �� ���������
//area - ������ ������� ���� �����

void dynamic_memory_test() {
	std::vector<Figure*> figures;

	bool proceed = true;
	while (proceed) {
		std::string command;
		std::cin >> command;

		if ("exit" == command) { proceed = false; continue; }
		if ("area" == command) {
			std::cout << "Full area: " << full_area(figures) << std::endl;
			continue;
		}
		if ("cir" == command) {
			//�� �� ����� ���������� Circle � �������������� ������, �.�. �� ������ ���� ����� ����������
			//�������� ��������� ����� - ������������� ������������ ������
			int radius;
			std::cin >> radius;
			auto cir_ptr = new Circle(radius);
			//��������� ��������� � �������
			figures.push_back(cir_ptr);
			continue;
		}
		if ("rect" == command) {
			int w,h;
			std::cin >> w >> h;
			auto rect_ptr = new Rectangle(w,h);
			figures.push_back(rect_ptr);
			continue;
		}

		std::cout << "Unknown command" << std::endl;
	}

	for (auto fig_ptr : figures) //����������� ������
		delete fig_ptr;
}

//� ���� ��������� ���� ���� ������ �����
//���� �� ���� �������� ������ �������� �� �������������� �������������, �� �� �� �������� ������ ��������, �.�. ����������� �������� �������� �� ���� �������
//�� ������, ��� ������� ���� ������ ����������� �������� ����������

int main() {
	if (false) dynamic_memory_test();

	return 0;
}