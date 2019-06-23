#include <iostream>
//� ��������� ������� ���������� ����������� �������������� �����, ������� ������� ����� ����� ����������� ������������

//���� �� ����������� ��� �� ���������� � �������������, �� ��� ����� ���� ����������� �������������, ������, ����� �������������� �������� upcasting (�������������� ����� �� ��������)
struct Base {
	virtual void say() const { std::cout << "Base" << std::endl; }
	virtual ~Base()  { }
};

struct Derived : Base {
	void say() const override { std::cout << "Derived" << std::endl; }
};

void upcasting_test() {
	Derived d;
	d.say();

	Base b = d; //����� ��������� �������������� ����� ��������������� - static_cast
	b.say(); //��������� Base::say() - �������� ����� ������, ��� ������������

	Base &b_ref = d; //����� ��������� �������������� ����� ������, �.�. ����� ������ �� ����� ��������, � ����� ������� ������ ����� ���������� � Derived ������� ���� Base
	b_ref.say(); //��������� Derived::say() - ����������� ��������

	Base *b_ptr = &d; //����� ��������� �� �� ����� - ��������� ������� ������ ���������� �������
	b_ptr->say(); //��������� Derived::say() - ����������� ��������
}

//���� ���� ������������� ��������� �������������� - �� �������� ������ � ����������� - �� ��� �� ����� ���� �������, �.�. �� ����� ���������� ��������� ����� �������������� ����������
//� ���� ������ �� ����� ������� �������������� ����
//�������������� �� �������� ������ � ����������� ���������� downcasting (�������������� ���� �� ��������)

struct Figure { //���������
	virtual double area() const = 0;
	virtual ~Figure() { }
};

class Circle  : public Figure {
public:
	Circle(double r): r(r) { }
	double area() const override { return 3.1415*r*r; }
	double radius() { return r;	} //���������� ����� ������ Circle

private:
	double r;
};

class Rectangle  : public Figure {
public:
	Rectangle(double w, double h): w(w), h(h) { }
	double area() const override { return w * h; }
	double width() const { return w; } //���������� ����� ������ Rectangle
	double heigth() const { return h; } //���������� ����� ������ Rectangle

private:
	double w, h;
};

void downcasting_test() {
	{
		Figure &fig_ref = *(new Circle(1.)); //������ ������ ���� Circle, �� ��������� ������ �� ���� � ������� �����
		std::cout << "Area = " << fig_ref.area() << std::endl;
		//fig_ref.radius(); //������ ����������! ������ ������� ����� .cir, �.�. Figure � �� ������ �� �����
		//Circle &cir_ref = fig_ref; //����� �������������� �� �����  ���� �������
		
		Circle &cir_ref = static_cast<Circle&>(fig_ref); //�� �� ����� ��������� ��� ����
		std::cout << "Radius = " << cir_ref.radius();

		delete &fig_ref;
	}

	{
		Figure *fig_ptr = new Rectangle(1., 2.);
		std::cout << "Area = " << fig_ptr->area() << std::endl;
		//Rectangle *rec_ptr = fig_ptr; //���������� ������������� ������
		Rectangle *rec_ptr = static_cast<Rectangle*>(fig_ptr); //���� ����� ��������� �������������� � � ����������
		std::cout << "Width/Heigth = " << rec_ptr->width() << "/" << rec_ptr->heigth() << std::endl;

		delete fig_ptr;
	}
}


//�������������� ����� �������� � ��� ������������� ������������
class Position {
public:
	Position(int x, int y) :x(x), y(y) { }

	int getX() const { return x; }
	int getY() const { return y; }

private:
	int const x, y;
};

class PositionedRectangle : public Position, public Rectangle {
public:
	PositionedRectangle(int x, int y, int w, int h) : Position(x, y), Rectangle(w, h) { }
};

int main() {
	if (false) upcasting_test();
	if (false) downcasting_test();

	return 0;
}