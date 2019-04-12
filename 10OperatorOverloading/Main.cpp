#include <iostream>

//���������� ���������� - ������ ��������, ����������� ������� ������ ������� ������� � ������� ����� �������

//���������� �������� �������������� ��������
class Velocity {
	double x, y;

public:
	Velocity(double x, double y) {
		Velocity::x = x;
		Velocity::y = y;
	}

	Velocity() : Velocity(0., 0.) {
	}

	void print() {
		std::cout << "(" << x << "," << y << ")" << std::endl;
	}
	//������ ������� ������ ����� ������ Velocity, ���������� ������ �������� ���� ����� ������ �������� � ��������� ��������
	Velocity summation(Velocity const &oth) {
		return Velocity(this->x + oth.x, this->y + oth.y);
	}

	//��� �� ����� �����, �� � ���� ���������
	Velocity operator+(Velocity const &oth) {
		return Velocity(this->x + oth.x, this->y + oth.y);
	}
};

void velocity_test() {
	double x1, y1, x2, y2;
	std::cout << "The first velocity components: " << std::flush;
	std::cin >> x1 >> y1;
	Velocity v1(x1, y1);

	std::cout << "The second velocity components: " << std::flush;
	std::cin >> x2 >> y2;
	Velocity v2(x2, y2);

	std::cout << "Total velocity components: " << std::endl;
	std::cout << "Direct call: "; v1.summation(v2).print();
	std::cout << "Operator call: "; (v1 + v2).print();
	std::cout << "Explicit operator call: "; v1.operator+(v2).print();
}

//����� �������� ����� ����������� ��� �������������� ���������: + - * = /
//������� ��������� ��������� � ������� �������� �� �����
class VelocityB {
	double x, y;

public:
	VelocityB(double x, double y) {
		VelocityB::x = x;
		VelocityB::y = y;
	}

	VelocityB() : VelocityB(0., 0.) {
	}

	void print() {
		std::cout << "(" << x << "," << y << ")" << std::endl;
	}
	
	//����� ������������� �������������� ����������
	VelocityB operator+(VelocityB const &oth) {
		return VelocityB(this->x + oth.x, this->y + oth.y);
	}

	VelocityB operator*(double d) {
		return VelocityB(d*this->x, d*this->y);
	}

	VelocityB operator/(double d) {
		return VelocityB(this->x / d, this->y / d);
	}
};

void velocityB_test() {
	VelocityB v1(10, 10);
	VelocityB v2(10, 10);

	auto v3 = v1 / 10;
	auto v4 = v2 * 10;
	v3.print(); v4.print();

	//������ � �������� ������� �������� �������� �� �����
	//auto v5 = 10 * v1; //������ ����������!
	//��� ������� � ���, ��� ���������� �� ����� ��������� �����
	//10.operator+(v1), �.�. 10 - ����� int, � int �� �������� �������...
}

//����� ��������� �������� � ������������� ����� � �������� � ���������� �������,
//������������� ������������ ���������� ������������� ��������� � ���� ���������� �������
VelocityB operator*(double lha, VelocityB &v) {
	return v * lha;
}

void velocityB_globalfunction_test() {
	VelocityB v1(10, 10);
	(21 * v1).print(); //�.�. ����� ����� ����� ������� ���������, �� ������� ������ ����������
}

//� C++ ����� �����������, �.�. �������� ����������� ���������� ��� �����, ����������� �������������, ����� ���������
//�����: . :: ?:
//� �������� �����������: sizeof � typeid

//�������������� ������������
//�� ����� ����������� ����� ���������, ��� += -= *= � �.�. 
//�������� ����� Point, � ������� ���������� ��� ��������
class Point {
	double x, y;
public:
	Point(double x, double y) {
		Point::x = x;
		Point::y = y;
	}

	Point() : Point(0., 0.) {
	}

	void print() {
		std::cout << "[" << x << "," << y << "]" << std::endl;
	}

	//�������� �������� �� ������������ ���: Point& - ��� ������ �� ������ ���� Point, �.�. �� �������� ������ � ����� �� ������ �� ���������������
	Point& operator+=(Point const &p) {
		this->x += p.x;
		this->y += p.y;
		return *this; //this - ��������� �� ������� ������, ������������� - ��� ������
	}

	Point& operator-=(Point const &p) {
		this->x += p.x;
		this->y += p.y;
		return *this;
	}

	Point& operator*=(double d) {
		this->x *= d;
		this->y *= d;
		return *this;
	}

	Point& operator/=(double d) {
		this->x /= d;
		this->y /= d;
		return *this;
	}
};

//� ������� �� ���������� + - * � /, �������������� ��������� ����� ������� ������ � ������, �� �� ���������� ��������

void arithmetic_test() {
	Point p(1, 1);
	Point q(-1, -1);

	(((p *= 2) += q) /= 2).print();
	p.print();
}


int main() {
	if (false) velocity_test();
	if (false) velocityB_test();
	if (false) velocityB_globalfunction_test();
	if (false) arithmetic_test();

	return 0;
}