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

class Circle final : public Figure {
public:
	Circle(double r): r(r) { }
	double area() const override { return 3.1415*r*r; }
	void cir() const { std::cout << "Cir" << std::endl; } //���������� ����� ������ Circle

private:
	double r;
};

class Rectangle final : public Figure {
public:
	Rectangle(double w, double h): w(w), h(h) { }
	double area() const override { return w * h; }
	void rec() const { std::cout << "Rec" << std::endl; } //���������� ����� ������ Rectangle

private:
	double w, h;
};

void downcasting_test() {
	{
		Figure &fig_ref = *(new Circle(1.)); //������ ������ ���� Circle, �� ��������� ������ �� ���� � ������� �����
		std::cout << fig_ref.area() << std::endl;
		//fig_ref.cir(); //������ ����������! ������ ������� ����� .cir, �.�. Figure � �� ������ �� �����
		//Circle &cir_ref = fig_ref; //����� �������������� �� �����  ���� �������
		
		Circle &cir_ref = static_cast<Circle&>(fig_ref); //�� �� ����� ��������� ��� ����
		cir_ref.cir();

		delete &fig_ref;
	}

	{
		Figure *fig_ptr = new Rectangle(1., 2.);
		std::cout << fig_ptr->area() << std::endl;
		//Rectangle *rec_ptr = fig_ptr; //���������� ������������� ������
		Rectangle *rec_ptr = static_cast<Rectangle*>(fig_ptr); //���� ����� ��������� �������������� � � ����������
		rec_ptr->rec();

		delete fig_ptr;
	}
}

int main() {
	if (false) upcasting_test();
	if (false) downcasting_test();

	return 0;
}