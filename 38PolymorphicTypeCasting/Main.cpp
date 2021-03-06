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
	double radius() const { return r;	} //���������� ����� ������ Circle

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
		//fig_ref.radius(); //������ ����������! ������ ������� ����� .cir, �.�. Figure � ��� ������ �� �����
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
struct Shape {
	virtual bool contains(double x, double y) const = 0;
	virtual ~Shape() { }
};

class Position {
public:
	Position(double x, double y) :x(x), y(y) { }

	double getX() const { return x; }
	double getY() const { return y; }

private:
	double const x, y;
};

#include <cmath>
class PositionedRectangle : public Position, public Rectangle, public Shape {
public:
	PositionedRectangle(double x, double y, double w, double h) : Position(x, y), Rectangle(w, h) { }
	bool contains(double x, double y) const override {
		return (x > Position::getX() && x < (Position::getX()+Rectangle::width()) && y > Position::getY() && y < (Position::getY()+Rectangle::heigth()));
	}
};

class PositionedCircle : public Position, public Circle, public Shape {
public:
	PositionedCircle(double x, double y, double r) : Position(x, y), Circle(r) { }
	bool contains(double x, double y) const override {
		return hypot(x - Position::getX(), y - Position::getY()) < Circle::radius();
	}
};

#include <string>
std::string in_out(double x, double y, Shape const &shape) {
	return shape.contains(x, y) ? "inside" : "outside";
}

void multiple_inheritance_cast_test() {
	Shape *shapeA = new PositionedCircle(0., 0., 1.);          //������� upcast
	Shape *shapeB = new PositionedRectangle(0., 0., 1., 1.);   //������� upcast
	std::cout << "The point (0.8,0.8) is \n"
		<< in_out(0.8, 0.8, *shapeA) << " the shapeA " << '\n'
		<< in_out(0.8, 0.8, *shapeB) << " the shapeB " << '\n'
		<< std::endl;

	//PositionedCircle *cir_ptr = shapeA; //���������� ������ ������� ��������������
	PositionedCircle *poscir_ptr = static_cast<PositionedCircle*>(shapeA); //�� ����� ����!
	//Circle *cir_ptr = static_cast<Circle*>(shapeA); //����������!
	//���� �� �����, ��� ��� ������ �������� ����������� Circle � ����� ���� � ���� �������, ���������� ����������� ����� �������������� ���� ����, �.�. ��� �������������� �� �������� �� upcast, �� downcast
	
	Circle *cir_ptr = (Circle*)(shapeA); //������ ������� ���!!!
	//� ����������� ���� ����� �������� reinterpret_cast<Circle*>
	//�� ������ ��������, �� ����������� ��� ������������� ��������������!!!
	//std::cout << cir_ptr->radius() << std::endl; //������������� ���������!!!
}

//static_cast ����� ������� ��� �� ��������� ��������������, ���� ��� � �������� ����������, ��� � ������ ������� ������� �� Shape � Circle ��� ������������� ������������
//������ static_cast ��������� ������ �� ������ ����������� ���������� � ����� � �� ����� ����������� �������� �������� ������������
void wrong_downcast_test() {
	Figure *fig = nullptr;
	std::cout 
		<< "1)Circle\n"
		<< "2)Recatangle\n" 
		<< std::endl;
	int x;
	std::cin >> x;
	switch (x) {
	case 1:
		fig = new Circle(1.);
		break;
	case 2:
		fig = new Rectangle(2., 3.);
		break;
	default:
		std::cout << "Unknown figure!" << std::endl;
		return;
	}

	Rectangle *rect_ptr = static_cast<Rectangle*>(fig); //��� ������! ������ �������, �.�. Circle � Figure - ������ ����� ��������, ������������ downcast
	//������ �������� ��� �������, �� ������� ��������� fig ����� ���� ������
	//��� ������� �� ������ ������������ � �� ����� ���� ����������
	std::cout << rect_ptr->heigth() << std::endl; //������������� ���������!!!
}

//����� �������������� �� "������������ ����", ������� ������������ � �������������� static_cast, C++ ������������ �������� �������������� �� ������������� ���� - dynamic_cast

//��� ����, ����� dynamic_cast ������� ���, ��� ���������, ���������� ���������� �������� �������  
//������ > �������� > �/C++ > ���� > �������� ���������� � ����� ������� ����������
//���� ��� ����� �� ��������, �� dynamic_cast ��������� ��� static_cast
void dynamic_check_downcast_test() {
	Figure *fig = nullptr;
	std::cout
		<< "1)Circle\n"
		<< "2)Recatangle\n"
		<< std::endl;
	int x;
	std::cin >> x;
	switch (x) {
	case 1:
		fig = new Circle(1.);
		break;
	case 2:
		fig = new Rectangle(2., 3.);
		break;
	default:
		std::cout << "Unknown figure!" << std::endl;
		return;
	}

	Rectangle *rect_ptr = dynamic_cast<Rectangle*>(fig);
	if (nullptr != rect_ptr)
		std::cout << rect_ptr->heigth() << std::endl;
	else
		std::cout << "Can't cast to Rectangle..." << std::endl;
}

void dynamic_reference_check_downcast_test() {
	Figure &fig = *(new Circle(1.));
	try {
		Rectangle &rec_ref = dynamic_cast<Rectangle&>(fig);
		std::cout  << rec_ref.heigth() << std::endl;
	}
	catch (std::bad_cast &ex) {
		std::cout << ex.what() << std::endl;
	}
	delete &fig;
}

int main() {
	if (false) upcasting_test();
	if (false) downcasting_test();
	if (false) multiple_inheritance_cast_test();
	if (false) wrong_downcast_test();
	if (false) dynamic_check_downcast_test();
	if (false) dynamic_reference_check_downcast_test();

	return 0;
}