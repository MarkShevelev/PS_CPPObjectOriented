#include <iostream>
#include <string>

//� ����� C++ � ��������� ��������� ���������� ����� ������� ������� ������������� ���� ��� ������ � ������
//����� ��������� ���������� "������� ���������������"
//��������, C++ ���������� ������� �������������� ����� � �������������� ���������

void overload_print(int i) {
	std::cout << "INT" << std::endl;
}

void overload_print(short sh) {
	std::cout << "SHORT" << std::endl;
}

void arithmetic_conversion_test() {
	short sh1 = 1, sh2 = 1;
	overload_print(sh1 + sh2); //� ����� ����������� INT
}

//����� �� �������������� ���������� ����� ����������� � � ��������

class Counter {
	int counter;
public:
	Counter(int begin) { //������� �������� �� ���� �����������, �� ��������� ������������ �������� ���� int
		counter = begin;
	}

	int next() { return counter++; }
};

void print_ten_counts(Counter c) {
	for (int i = 0; i != 10; ++i)
		std::cout << c.next() << ' ';
	std::cout << std::endl;
}

void print_ten_counts_test() {
	Counter c(10);
	print_ten_counts(c);

	int i = 10;
	print_ten_counts(i); //��� �� �����������, �� ���� ����� ������� ��������!
}

//��� ���������� ������� ��������������� ����������� ������������
//���� � ������ ���� ����������� � ����� ����������, �� ���������� ����� ������������ ��� ��� �������������� ����
//��������, ��� �������� �������������� ������� �������� � ������
void print_string(std::string s) {
	std::cout << s << std::endl;
}

void print_string_test() {
	std::string s1("Hello"); //������� ��������, ��� � ������ std::string ���� ����������� � ����� ���������� char const *
	print_string(s1);

	char const *s2 = "World!";
	print_string(s2); //������ ��� ���������� ���������� � ���� ������, ������ �������� ����� �����
}

//� ��������������  copy-list-initialization ����� ������� �������������� �� ������ ���������� � ������ �������� ��� ������������� � ����������� �����������
class Point {
	double x, y;
public:
	Point(double x, double y) {
		Point::x = x;
		Point::y = y;
	}

	void print() {
		std::cout << "(" << x << "," << y << ")" << std::endl;
	}
};

void print_point(Point p) {
	p.print();
}

void print_point_test() {
	Point p(1., -1);
	print_point(p);

	print_point({ 2.,-2 });
}

//� ��������� ��������� ����� ��������� ����� ��������� �������������
//����� �� ����� ������� �����������, ��� �����-�� ����������� ������ ������������ ��� �������� ��������������
class Date {
	int month, day;

public:
	explicit Date(int month, int day) {
		Date::month = month;
		Date::day = day;
	}

	int get_month() { return month; }
	int get_day() { return day; }
};

void print_date(Date d) {
	std::cout << d.get_month() << "-" << d.get_day() << std::endl;
}

void print_date_test() {
	Date d(10, 5);
	print_date(d);

	//print_date({ 12,31 }); //������ ����������! ���������� ��������� copy-list-initializer
	//��-�������� ����� ������� ��������������� ���������� ������� ����
	print_date(Date{ 12,31 });
}

int main() {
	if (false) arithmetic_conversion_test();
	if (false) print_ten_counts_test();
	if (false) print_string_test();
	if (false) print_point_test();
	if (false) print_date_test();
}