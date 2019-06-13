#include <iostream>
#include <string>

//���������� ������������� ������������ - ��� ��������, ����� ����� ��������� �� ������, � ���������� ������������ �������

struct PositivePredicate {
	bool check(int x) const { return x > 0; }
};

struct EvenPredicate {
	bool check(int x) const { return 0 == x % 2; }
};

struct EvenPositivePredicate : private PositivePredicate, private EvenPredicate {
	bool check(int x) const { return PositivePredicate::check(x) && EvenPredicate::check(x); }
};

void multiple_private_inheritance_test() {
	int i;
	std::cin >> i;
	std::cout << std::boolalpha << EvenPositivePredicate().check(i) << std::endl;
}

//��� ������������� ������������ �� �������� �������� ��� �� ������ ������, � ����������
//����������� ����� ������ ���������� �������, �� ������ ����������� ������ ������ � ���� �� ������
/*
struct DoublePositivePredicate: private PositivePredicate, private PositivePredicate {
	bool check(int x) const { return PositivePredicate::check(x); }
};
*/
//��������, ��� ����� ������������ ��������, �� ��� ����� ��� �������� ������ PositivePredicate, ��� ����������� ��������� ���� ��������� ������������� PositivePredicate �� �������
struct FirstPositivePredicate : private PositivePredicate {
	bool check(int x) const { return PositivePredicate::check(x); }
};

struct SecondPositivePredicate : private FirstPositivePredicate, private PositivePredicate {
	bool check(int x) const { return PositivePredicate::check(x) && FirstPositivePredicate::check(x); }
};

//������ ���� ����������, ��� �� ����� ������ ������������ ������ � ���� �� ������ ����������� ���������� ���������:
//������� �� ��������� ������ ��� ������ PositivePredicate, �������� �������� ����� FirstPositivePredicate, ������� ������ �������� � ���� �������� PositivePredicate,
//����� �� ��������� ��� ��� PositivePredicate, �� � ��� ��� ������ �������������� ������, ��������� ���� � ���������� ������ SecondPositivePredicate ������, �� �� ����� ���������: ���� - ���������������� ������, �� ������� �� �������� ������, ������ ������� ������, ������� ���������� � ������ ���������

//�������� ������������� ������������ ����� ������ ������� �������, ������� �������� ������������ ���������� ����������
class Rectangle {
public:
	Rectangle(int w, int h): w(w), h(h) { }

	int getW() const { return w; }
	int getH() const { return h; }

private:
	int const w, h;
};

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

	bool in_rect(int x, int y) const { return x > getX() && x < getX() + getW() && y > getY() && y < getY() + getH(); }
};

void rectangle_area(Rectangle const &rect) {
	std::cout << "Area: " << rect.getH()*rect.getW() << std::endl;
}

void position_distance(Position const &lha, Position const &rha) {
	std::cout << "Distance: " << std::hypot(lha.getX() - rha.getX(), lha.getY() - rha.getY());
}

void multiple_public_inheritance_test() {
	PositionedRectangle a(0, 0, 10, 20), b(0, 1, 20, 30);
	rectangle_area(a); rectangle_area(b);
	position_distance(a, b);
}

//������� ������ PositionedRectangle ��������� �������� ��� ������ Rectangle, ��� � ������ Position

//������ �������� �������������� ������������ �������� ������ � ������ ������
//��� ��������� ������������ ����� ���������� ������� �������� ������ ������ ��������� � ������� ������ ������� ����������� ������
void multiple_inheritance_address_test() {
	PositionedRectangle pr(0, 0, 10, 10);
	void *pr_ptr = &pr;
	Position *pos_ptr = &pr;
	Rectangle *rect_ptr = &pr; //��� ������������ ������� � ����������� ����������

	std::cout << std::boolalpha
		<< "PositionedRectangle ? Position: " << (&pr == pos_ptr) << '\n' 
		<< "PositionedRectangle ? Rectangle: " << (&pr == rect_ptr) << '\n'
		<< "PositionedRectangle ? Rectangle: " << (pr_ptr == rect_ptr) << std::endl;
	std::cout << &pr << '\n' << pos_ptr << '\n' << rect_ptr << std::endl;
}
//�������� �����, ������� �������� � ���������� pr_ptr, ���������� �� ������ ������� pr, �� ��� ��������� rect_ptr � ������� pr ����� �������� ������ �����

int main() {
	if (false) multiple_private_inheritance_test();
	if (false) multiple_public_inheritance_test();
	if (false) multiple_inheritance_address_test();

	return 0;
}